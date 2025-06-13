#include "event_content_list_model.hpp"
#include "event.hpp"


void EventContentListModel::load(Event *event)
{
	currentEvent = event;
	emit dataChanged(index(0), index(rowCount()));
}

int EventContentListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return currentEvent ? currentEvent->list.size() : 0;
}

QVariant EventContentListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::UserRole + 0)
		return QVariant::fromValue(currentEvent);

	if (role == Qt::UserRole + 1)
	{
		Command::It it = currentEvent->list.begin();
		std::advance(it, index.row());
		return QVariant::fromValue(it);
	}

	return QVariant();
}
