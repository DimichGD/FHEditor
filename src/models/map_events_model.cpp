#include "map_events_model.hpp"

MapEventsModel::MapEventsModel(QObject *parent)
	: BaseModel2(&accessor, parent) {}

MapEvent *MapEventsModel::mapEvent(int row)
{
	return accessor.value(row + 1);
}

void MapEventsModel::setEvents(std::vector<std::optional<MapEvent> > *events)
{
	accessor = Accessor<MapEvent>(events);
}

QVariant MapEventsModel::data(int row, int column) const
{
	const MapEvent *mapEvent = accessor.value(row);
	if (!mapEvent)
		return QVariant(); // TODO: filter null events

	switch (column)
	{
		case MapEvent::ID: return mapEvent->id;
		case MapEvent::NAME: return mapEvent->name;
		case MapEvent::NOTE: return mapEvent->note;
		case MapEvent::POS_X: return mapEvent->x;
		case MapEvent::POS_Y: return mapEvent->y;
		default: qDebug() << "MapEventsModel::data column" << column << "does not exist";
	}

	return QVariant();
}

void MapEventsModel::setData(int row, int column, const QVariant &value)
{
	MapEvent *mapEvent = accessor.value(row);
	if (!mapEvent)
		return;

	switch (column)
	{
		case MapEvent::ID: mapEvent->id = value.toInt(); break;
		case MapEvent::NAME: mapEvent->name = value.toString(); break;
		case MapEvent::NOTE: mapEvent->note = value.toString(); break;
		case MapEvent::POS_X: mapEvent->x = value.toInt(); break;
		case MapEvent::POS_Y: mapEvent->y = value.toInt(); break;
		default: qDebug() << "MapEventsModel::setData column" << column << "does not exist";
	}
}

/*int MapEventsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return accessor.size();
}

int MapEventsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return MapEvent::COUNT;
}

QVariant MapEventsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (!hasIndex(index.row(), index.column()))
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	if (!accessor.hasElement(index.row()))
		return QVariant();

	const MapEvent *mapEvent = accessor.value(index.row());
	if (!mapEvent)
		return QVariant();

	switch (index.column())
	{
		case MapEvent::ID: return mapEvent->id;
		case MapEvent::NAME: return mapEvent->name;
		case MapEvent::NOTE: return mapEvent->note;
		case MapEvent::POS_X: return mapEvent->x;
		case MapEvent::POS_Y: return mapEvent->y;
		default: qDebug() << "MapEventsModel::data column" << index.column() << "does not exist";
	}

	return QVariant();
}

bool MapEventsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	if (!hasIndex(index.row(), index.column()))
		return false;

	if (role != Qt::EditRole)
		return false;

	MapEvent *mapEvent = accessor.value(index.row());
	if (!mapEvent)
		return false;

	switch (index.column())
	{
		case MapEvent::ID: mapEvent->id = value.toInt(); break;
		case MapEvent::NAME: mapEvent->name = value.toString(); break;
		case MapEvent::NOTE: mapEvent->note = value.toString(); break;
		case MapEvent::POS_X: mapEvent->x = value.toInt(); break;
		case MapEvent::POS_Y: mapEvent->y = value.toInt(); break;
		default: qDebug() << "MapEventsModel::setData column" << index.column() << "does not exist";
	}

	return true;
}*/


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

/*QVariant MapEventsModel::displayRoleData(int row, int column, Triple pointer) const
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
	return QVariant();
}

void MapEventsModel::setEditRoleData(int row, int column, const QVariant &value)
{

}*/
