#include "event_content_list.hpp"
#include "command_factory.hpp"
//#include "event.hpp"
//#include "database.hpp"
#include "event_content_list_model.hpp"
#include "event_content_selection_model.hpp"
#include "events/command_text_dialog.hpp"
#include "events/create_command_dialog.hpp"

#include <QStyledItemDelegate>
#include <QMenu>

class EventItemDelegate: public QStyledItemDelegate
{
public:
	EventItemDelegate(QObject *parent = nullptr): QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		QRect rect = option.rect;
		QStyledItemDelegate::paint(painter, option, index);

		painter->save();
		auto cmd1 = index.data(Qt::UserRole + 1).value<Command::It>();
		cmd1->parameters->draw(painter, option.state & QStyle::State_Selected, rect, cmd1->indent);
		painter->restore();
	}
};

EventContentList::EventContentList(QWidget *parent): QListView(parent)
{
	this->setItemDelegateForColumn(0, new EventItemDelegate(this));

	model = new EventContentListModel(this);
	setModel(model);
	setSelectionModel(new EventContentSelectionModel(model, this));

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

void EventContentList::loadList(Event *event, std::list<Command> *list)
{
	currentList = list;
	//currentEvent = event;
	model->load(event);
}

void EventContentList::actionCommandNewTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selection()[0].indexes();

	CreateCommandDialog dialog(selectedIndices[0], this);
	if (dialog.exec())
	{
		emit model->dataChanged(model->index(0), model->index(model->rowCount()));
		selectionModel()->select(selectedIndices[0], QItemSelectionModel::Select);
	}
}

void EventContentList::actionCommandEditTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	QDialog *dialog = nullptr;
	auto selectedIndices = selectionModel()->selection()[0].indexes();
	Command::It command = selectedIndices[0].data(Qt::UserRole + 1).value<Command::It>();

	switch (command->code)
	{
		case CommandFactory::TEXT: dialog = new CommandTextDialog(true, selectedIndices, this); break;
	}

	if (dialog && dialog->exec())
	{
		selectionModel()->select(selectedIndices[0], QItemSelectionModel::Select);
		emit model->dataChanged(model->index(0), model->index(model->rowCount())); // TODO: narrow range
	}
}

void EventContentList::actionCommandDeleteTriggered(bool)
{
	if (!selectionModel()->hasSelection())
		return;

	auto selectedIndices = selectionModel()->selection()[0].indexes();
	Command::It command = selectedIndices[0].data(Qt::UserRole + 1).value<Command::It>();
	for (int i = 0; i < selectedIndices.size(); i++)
		command = currentList->erase(command);

	selectionModel()->clearSelection();
	emit model->dataChanged(model->index(0), model->index(model->rowCount()));
}

void EventContentList::contextMenuRequested(const QPoint &pos)
{
	QModelIndex index = indexAt(pos);
	if (index.isValid())
	{
		Command::It command = index.data(Qt::UserRole + 1).value<Command::It>();

		actionCommandNew->setEnabled(command->parameters->canAdd());
		actionCommandEdit->setEnabled(command->parameters->canEdit());
		actionCommandDelete->setEnabled(command->parameters->canDelete());
	}
	else
	{
		actionCommandNew->setEnabled(false);
		actionCommandEdit->setEnabled(false);
		actionCommandDelete->setEnabled(false);
	}

	contextMenu->exec(viewport()->mapToGlobal(pos));
}
