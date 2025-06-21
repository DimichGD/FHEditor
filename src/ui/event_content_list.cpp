#include "event_content_list.hpp"
#include "command_factory.hpp"
//#include "event.hpp"
//#include "database.hpp"
#include "event_content_list_model.hpp"
#include "event_content_selection_model.hpp"
#include "events/command_text_dialog.hpp"
#include "events/create_command_dialog.hpp"
#include "play_sound_dialog.hpp"

#include <QStyledItemDelegate>
#include <QMenu>

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
		auto cmd1 = index.data(Qt::UserRole + 1).value<Command::Iterator>();
		cmd1->parameters->draw(painter, option.state & QStyle::State_Selected, rect, cmd1->indent);
		painter->restore();
	}
};

EventContentList::EventContentList(QWidget *parent): QListView(parent)
{
	this->setItemDelegateForColumn(0, new EventItemDelegate(this));

	/*model = new EventContentListModel(this);
	setModel(model);
	setSelectionModel(new EventContentSelectionModel(model, this));*/

	actionCommandNew = new QAction("New", this);
	actionCommandEdit = new QAction("Edit", this);
	actionCommandDelete = new QAction("Delete", this);
	contextMenu = new QMenu(this);
	contextMenu->addAction(actionCommandNew);
	contextMenu->addAction(actionCommandEdit);
	contextMenu->addSeparator();
	contextMenu->addAction(actionCommandDelete);

	connect(actionCommandNew, &QAction::triggered, this, &EventContentList::actionCommandNewTriggered);
	connect(actionCommandEdit, &QAction::triggered, this, &EventContentList::actionCommandEditTriggered);
	connect(actionCommandDelete, &QAction::triggered, this, &EventContentList::actionCommandDeleteTriggered);
	connect(this, &EventContentList::customContextMenuRequested, this, &EventContentList::contextMenuRequested);
}

void EventContentList::loadList(std::list<Command> *list)
{
	//currentList = list;

	for (auto &command: *list)
	{
		command.parameters = CommandFactory::createCommand2(command.code);
		command.parameters->read(command.jsonValues);
	}

	model = new EventContentListModel(list, this);

	setModel(model);
	setSelectionModel(new EventContentSelectionModel(model, this));
}

void EventContentList::clear()
{
	setModel(nullptr);

	if (model)
		delete model;
}

void EventContentList::actionCommandNewTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selection()[0].indexes();

	CreateCommandDialog dialog(selectedIndices[0], this);
	if (dialog.exec())
	{
		int firstRow = selectedIndices[0].row();
		model->insertCommands(firstRow, dialog.resultCommands());

		selectionModel()->clearSelection();
		setCurrentIndex(model->index(firstRow));
	}
}

void EventContentList::actionCommandEditTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	CommandDialog *dialog = nullptr;
	auto selectedIndices = selectionModel()->selection()[0].indexes();
	Command::Iterator command = selectedIndices[0].data(Qt::UserRole + 1).value<Command::Iterator>();

	switch (command->code)
	{
		case CommandFactory::TEXT: dialog = new CommandTextDialog(true, selectedIndices, this); break;
		case CommandFactory::PLAY_BGM: dialog = new PlaySoundDialog(CommandSound::BGM, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_BGS: dialog = new PlaySoundDialog(CommandSound::BGS, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_ME: dialog = new PlaySoundDialog(CommandSound::ME, true, selectedIndices[0], this); break;
		case CommandFactory::PLAY_SE: dialog = new PlaySoundDialog(CommandSound::SE, true, selectedIndices[0], this); break;
	}

	if (dialog && dialog->exec())
	{
		int firstRow = selectedIndices[0].row();
		model->removeCommands(firstRow, selectedIndices.size());
		model->insertCommands(firstRow, dialog->resultCommands());

		selectionModel()->clearSelection();
		setCurrentIndex(model->index(firstRow));

		delete dialog;
	}
}

void EventContentList::actionCommandDeleteTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selection()[0].indexes();

	int firstRow = selectedIndices[0].row();
	model->removeCommands(firstRow, selectedIndices.size());
}

void EventContentList::contextMenuRequested(const QPoint &pos)
{
	QModelIndex index = indexAt(pos);
	if (index.isValid())
	{
		Command::Iterator command = index.data(Qt::UserRole + 1).value<Command::Iterator>();

		actionCommandNew->setEnabled(command->parameters->flags() & ICommandParams::CAN_ADD);
		actionCommandEdit->setEnabled(command->parameters->flags() & ICommandParams::CAN_EDIT);
		actionCommandDelete->setEnabled(command->parameters->flags() & ICommandParams::CAN_DELETE);

		selectionModel()->clearSelection();
		setCurrentIndex(index);
	}
	else
	{
		actionCommandNew->setEnabled(false);
		actionCommandEdit->setEnabled(false);
		actionCommandDelete->setEnabled(false);
	}

	contextMenu->exec(viewport()->mapToGlobal(pos));
}
