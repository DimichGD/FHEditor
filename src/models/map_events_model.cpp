#include "map_events_model.hpp"


/*int MapEventsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return currentMap->events.size();
}

int MapEventsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return 2;
}

QVariant MapEventsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	if (!currentMap->events.at(index.row()).has_value())
		return QVariant();

	switch (index.column())
	{
		case 0: return currentMap->events.at(index.row()).value().id;
		case 1: return currentMap->events.at(index.row()).value().name;
		//case Qt::EditRole: return dataForMapper(index.row(), index.column());
		//case Qt::DecorationRole: return iconForDisplay(index.row(), index.column());
	};

	return QVariant();
}*/

QVariant MapEventsModel::displayRoleData(int row, int column, Triple pointer) const
{
	const MapEvent *event = accessor.value(row);
	if (!event)
		return QVariant();

	if (column == 0) return event->id;
	if (column == 1) return event->name;

	return QVariant();
}

QVariant MapEventsModel::editRoleData(int row, int column, Triple pointer) const
{

}

QVariant MapEventsModel::userRoleData(int row, int column, Triple pointer) const
{

}

void MapEventsModel::setEditRoleData(int row, int column, const QVariant &value, Triple pointer)
{

}
