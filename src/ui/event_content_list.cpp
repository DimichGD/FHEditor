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
	this->setItemDelegateForColumn(0, new EventItemDelegate(this));
}

void EventContentList::loadList(std::list<Command> *list)
{
	clear();

	QFontMetrics metrics = fontMetrics();
	for (auto &command: *list)
		command.parameters->calculateWidth(metrics, command.indent);

	model = new EventContentListModel(list, this);

	setModel(model);
	setSelectionModel(new EventContentSelectionModel(model, this));
}

void EventContentList::clear()
{
	/*setModel(nullptr);

	if (model)
		delete model;*/
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
	Command::Iterator command = Command::iteratorFromIndex(selectedIndices[0]);

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
