#include "event_content_list.hpp"
#include "command_factory.hpp"
//#include "event.hpp"
//#include "database.hpp"
#include "conditional_branch_dialog.hpp"
#include "event_content_list_model.hpp"
#include "event_content_selection_model.hpp"
#include "events/command_text_dialog.hpp"
#include "events/create_command_dialog.hpp"
#include "menu.hpp"
#include "play_sound_dialog.hpp"
#include "wait_dialog.hpp"

#include <QStyledItemDelegate>
#include <QMenu>

#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>

class EventItemDelegate: public QStyledItemDelegate
{
public:
	EventItemDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		if (!index.isValid())
			return;

		QRect rect = option.rect;
		QStyledItemDelegate::paint(painter, option, index);

		painter->save();
		Command::Iterator command = Command::iteratorFromIndex(index);
		command->parameters->draw(painter, option.state & QStyle::State_Selected, rect, command->indent);
		painter->restore();
	}

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		Command::Iterator command = Command::iteratorFromIndex(index);

		QSize size = QStyledItemDelegate::sizeHint(option, index);
		if (command->parameters->totalWidth)
			size.setWidth(command->parameters->totalWidth);

		return size;
	}
};

EventContentList::EventContentList(QWidget *parent): QListView(parent)
{
	actionCommandNew = new QAction("New", contextMenu);
	actionCommandEdit = new QAction("Edit", contextMenu);
	actionCommandDelete = new QAction("Delete", contextMenu);
	actionCommandDelete->setShortcut(QKeySequence::Delete);
	addAction(actionCommandDelete);
	contextMenu = createMenu(this,
		{ actionCommandNew, actionCommandEdit, nullptr, actionCommandDelete });

	connect(actionCommandNew, &QAction::triggered, this, &EventContentList::actionCommandNewTriggered);
	connect(actionCommandEdit, &QAction::triggered, this, &EventContentList::actionCommandEditTriggered);
	connect(actionCommandDelete, &QAction::triggered, this, &EventContentList::actionCommandDeleteTriggered);
	connect(this, &EventContentList::customContextMenuRequested, this, &EventContentList::contextMenuRequested);

	this->setItemDelegateForColumn(0, new EventItemDelegate(this));

	model = new EventContentListModel(this);

	setModel(model);
	setSelectionModel(new EventContentSelectionModel(model, this));

	connect(this, &QListView::doubleClicked, [this](const QModelIndex &index)
	{
		if (Command::iteratorFromIndex(index)->code == 0)
			actionCommandNew->trigger();

		else
			actionCommandEdit->trigger();
	});

	// this signal not fired when selecting new item inside old selection range
	// TODO: need to come up with different selection solution
	connect(selectionModel(), &QItemSelectionModel::selectionChanged,
			[this](const QItemSelection &selected, const QItemSelection &)
	{
		if (!selected.empty()/* && selected[0].indexes()[0].isValid()*/)
		{
			auto selectedIndices = selectionModel()->selectedIndexes();
			std::sort(selectedIndices.begin(), selectedIndices.end(),
				[](const QModelIndex &a, const QModelIndex &b) -> bool
					{ return a.row() < b.row(); });

			auto parameters = Command::iteratorFromIndex(selectedIndices[0])->parameters;

			actionCommandNew->setEnabled(parameters->flags() & ICommandParams::CAN_ADD);
			actionCommandEdit->setEnabled(parameters->flags() & ICommandParams::CAN_EDIT);
			actionCommandDelete->setEnabled(parameters->flags() & ICommandParams::CAN_DELETE);
		}
		else
		{
			actionCommandNew->setEnabled(false);
			actionCommandEdit->setEnabled(false);
			actionCommandDelete->setEnabled(false);
		}
	});



	/*connect(selectionModel(), &QItemSelectionModel::currentRowChanged, [this](const QModelIndex &current, const QModelIndex &previous)
	{
		if (current.isValid())
		{
			auto parameters = Command::iteratorFromIndex(current)->parameters;

			actionCommandNew->setEnabled(parameters->flags() & ICommandParams::CAN_ADD);
			actionCommandEdit->setEnabled(parameters->flags() & ICommandParams::CAN_EDIT);
			actionCommandDelete->setEnabled(parameters->flags() & ICommandParams::CAN_DELETE);

			enum Strategy { SELECT_UNTIL, SELECT_WHILE };
			struct Holder { int endCode; Strategy strategy; };
			static std::map<int, Holder> codesMap = {
				{ CommandFactory::TEXT,          { CommandFactory::TEXT_LINE,    SELECT_WHILE } },
				{ CommandFactory::COMMENT,       { CommandFactory::COMMENT_LINE, SELECT_WHILE } },
				{ CommandFactory::BEGIN_CHOICES, { CommandFactory::END_CHOICES,  SELECT_UNTIL } },
				{ CommandFactory::IF,            { CommandFactory::END_IF     ,  SELECT_UNTIL } },
				{ CommandFactory::LOOP,          { CommandFactory::REPEAT_LOOP,  SELECT_UNTIL } },
			};

			QModelIndex first = current;
			QModelIndex last = current;

			Command::Iterator command = Command::iteratorFromIndex(first);
			int startCode = command->code;
			int startIndent = command->indent;

			auto it = codesMap.find(startCode);
			if (it == codesMap.end())
			{
				selectionModel()->clearSelection();
				return;
			}

			int endCode = it->second.endCode;
			Strategy strategy = it->second.strategy;

			std::advance(command, 1);
			while (true)
			{
				last = model->index(last.row() + 1, 0);
				if (strategy == SELECT_WHILE
					&& std::next(command)->code != endCode)
					break;

				if (strategy == SELECT_UNTIL
					&& command->code == endCode
					&& command->indent == startIndent)
					break;

				std::advance(command, 1);
			}

			//qDebug() << selectionModel()->currentIndex();

			//QItemSelection rowSelection(first, last);
			QItemSelection rowSelection(model->index(first.row() + 1), last);
			selectionModel()->clearSelection();
			selectionModel()->select(rowSelection, QItemSelectionModel::ClearAndSelect);

			//qDebug() << selectionModel()->selection()[0].indexes();

			//QItemSelection rowSelection2(first, first);
			//selectionModel()->select(rowSelection2, QItemSelectionModel::SelectCurrent);
		}
		else
		{
			qDebug() << "not valid";
			actionCommandNew->setEnabled(false);
			actionCommandEdit->setEnabled(false);
			actionCommandDelete->setEnabled(false);
		}
	});*/
}

void EventContentList::loadList(std::list<Command> *list)
{
	model->load(list);

	QFontMetrics metrics = fontMetrics();
	for (auto &command: *list)
		command.parameters->calculateWidth(metrics, command.indent);
}

void EventContentList::clear()
{
	model->load(nullptr);
}

void EventContentList::actionCommandNewTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	//auto selectedIndices = selectionModel()->selection()[0].indexes();
	auto index = selectionModel()->currentIndex();

	CreateCommandDialog dialog(index, this);
	if (dialog.exec())
	{
		int firstRow = index.row();
		model->insertCommands(firstRow, dialog.resultCommands());

		selectionModel()->clear();
		setCurrentIndex(model->index(firstRow));
	}
}

void EventContentList::actionCommandEditTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selectedIndexes();
	std::sort(selectedIndices.begin(), selectedIndices.end(),
		[](const QModelIndex &a, const QModelIndex &b) -> bool
			{ return a.row() < b.row(); });

	CommandDialog *dialog = nullptr;
	Command::Iterator command = Command::iteratorFromIndex(selectedIndices[0]);
	switch (command->code)
	{
		case CommandFactory::TEXT: dialog = new CommandTextDialog(true, selectedIndices, this); break;
		case CommandFactory::WAIT: dialog = new CommandWaitDialog(true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_BGM: dialog = new PlaySoundDialog(CommandSound::BGM, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_BGS: dialog = new PlaySoundDialog(CommandSound::BGS, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_ME: dialog = new PlaySoundDialog(CommandSound::ME, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_SE: dialog = new PlaySoundDialog(CommandSound::SE, true, selectedIndices[0], this); break;
		case CommandFactory::IF: dialog = new ConditionalBranchDialog(true, selectedIndices, this); break;
	}

	if (dialog && dialog->exec())
	{
		int firstRow = selectedIndices[0].row();
		model->removeCommands(firstRow, selectedIndices.size());
		model->insertCommands(firstRow, dialog->resultCommands());

		selectionModel()->clear();
		setCurrentIndex(model->index(firstRow));

		delete dialog;
	}
}

void EventContentList::actionCommandDeleteTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selectedIndexes();
	std::sort(selectedIndices.begin(), selectedIndices.end(),
		[](const QModelIndex &a, const QModelIndex &b) -> bool
			{ return a.row() < b.row(); });

	int firstRow = selectedIndices[0].row();
	model->removeCommands(firstRow, selectedIndices.size());
}

void EventContentList::contextMenuRequested(const QPoint &pos)
{
	/*QModelIndex index = indexAt(pos);
	if (index.isValid())
	{
		auto parameters = Command::iteratorFromIndex(index)->parameters;

		actionCommandNew->setEnabled(parameters->flags() & ICommandParams::CAN_ADD);
		actionCommandEdit->setEnabled(parameters->flags() & ICommandParams::CAN_EDIT);
		actionCommandDelete->setEnabled(parameters->flags() & ICommandParams::CAN_DELETE);
	}
	else
	{
		actionCommandNew->setEnabled(false);
		actionCommandEdit->setEnabled(false);
		actionCommandDelete->setEnabled(false);
	}*/

	contextMenu->exec(viewport()->mapToGlobal(pos));
}
