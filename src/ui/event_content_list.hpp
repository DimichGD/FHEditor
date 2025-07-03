#pragma once
//#include <QTreeWidget>
#include "event.hpp"
#include "event_content_list_model.hpp"
//#include "event_content_selection_model.hpp"
#include <QListView>
#include <QUndoStack>

/*class NewCommand: public QUndoCommand
{
public:
	NewCommand(EventContentListModel *model, QItemSelectionModel *selection,
			   std::list<Command> &&commands, int row)
	{
		this->model = model;
		this->selection = selection;
		this->commands = commands;
		this->row = row;
		setText("Add Command " + QString::number(commands.begin()->code));
	}

	void undo() override
	{
		model->removeCommands(row, commands.size());
		selection->select(model->index(row), QItemSelectionModel::ClearAndSelect);
	}

	void redo() override
	{
		model->insertCommands(row, commands);
		selection->select(model->index(row), QItemSelectionModel::ClearAndSelect);
	}

private:
	EventContentListModel *model = nullptr;
	QItemSelectionModel *selection = nullptr;
	std::list<Command> commands;
	int row;
};*/

class QMenu;
class EventContentListModel;

class EventContentList: public QListView
{
	Q_OBJECT

public:
	EventContentList(QWidget *parent = nullptr);
	void loadList(std::list<Command> *list);

	//QUndoStack *undoStack = nullptr;

public slots:
	void actionCommandNewTriggered(bool);
	void actionCommandEditTriggered(bool);
	void actionCommandDeleteTriggered(bool);
	void contextMenuRequested(const QPoint &pos);

private:
	EventContentListModel *model = nullptr;
	QMenu *contextMenu = nullptr;
	QAction *actionCommandNew = nullptr;
	QAction *actionCommandEdit = nullptr;
	QAction *actionCommandDelete = nullptr;
	QAction *undoAction = nullptr;
	QAction *redoAction = nullptr;
};


