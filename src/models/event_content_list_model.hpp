#pragma once
#include "event.hpp"
#include "common_events_model.hpp"
#include <QAbstractListModel>

class EventContentListModel: public QAbstractListModel
{
	Q_OBJECT

public:
	//explicit EventContentListModel(std::list<Command> *list, QObject *parent = nullptr);
	EventContentListModel(QObject *parent);
	void load(std::list<Command> *list);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;

	void removeCommands(int row, int count);
	void insertCommands(int row, std::list<Command> otherList);

private:
	CommonEventsModel *model = nullptr;
	std::list<Command> *commandList = nullptr;
};

