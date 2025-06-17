#pragma once
#include <QAbstractListModel>

class Event;
class EventContentListModel: public QAbstractListModel
{
	Q_OBJECT

public:
	explicit EventContentListModel(QObject *parent = nullptr): QAbstractListModel(parent) {}
	void load(Event *event);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;

private:
	//std::list<
	Event *currentEvent = nullptr;
};

