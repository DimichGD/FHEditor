#pragma once
#include "event.hpp"
#include <QAbstractListModel>

//class Event;
class EventContentListModel: public QAbstractListModel
{
	Q_OBJECT

public:
	explicit EventContentListModel(QObject *parent = nullptr): QAbstractListModel(parent) {}
	void load(std::list<Command> *list);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;

	void removeCommands(int row, int count);
	void insertCommands(int row, std::list<Command> &&otherList);

private:
	std::list<Command> *commandList = nullptr;
	//Event *currentEvent = nullptr;
};

