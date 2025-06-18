#pragma once
//#include <QTreeWidget>
#include "event.hpp"
#include <QListView>

//class Event;
class QMenu;
class EventContentListModel;

class EventContentList: public QListView
{
	Q_OBJECT

public:
	EventContentList(QWidget *parent = nullptr);
	void loadList(std::list<Command> *list);

public slots:
	void actionCommandNewTriggered(bool);
	void actionCommandEditTriggered(bool);
	void actionCommandDeleteTriggered(bool);
	void contextMenuRequested(const QPoint &pos);

private:
	//Event *currentEvent = nullptr;
	QMenu *contextMenu = nullptr;
	QAction *actionCommandNew = nullptr;
	QAction *actionCommandEdit = nullptr;
	QAction *actionCommandDelete = nullptr;

	std::list<Command> *currentList = nullptr;
	EventContentListModel *model = nullptr;
};


