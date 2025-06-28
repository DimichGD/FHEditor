#include "common_events_model.hpp"

Event *CommonEventsModel::eventFromRow(int row)
{
	// TODO: check for valid id
	return accessor.value(row);
}

QVariant CommonEventsModel::displayRoleData(int row, int column, Triple) const
{
	const Event *event = accessor.value(row);
	if (!event)
		return QVariant();

	if (column == 0) return event->id;
	if (column == 1) return event->name;

	return QVariant();
}

QVariant CommonEventsModel::editRoleData(int row, int column, Triple) const
{
	const Event *event = accessor.value(row);
	if (!event)
		return QVariant();


	switch (column)
	{
		case Event::ID: return event->id;
		case Event::NAME: return event->name;
		case Event::SWITCH_ID: return event->switchId;
		case Event::TRIGGER: return event->trigger;
	}

	qDebug() << "EventModel::dataForMapper column" << column << "does not exist";
	return QVariant();
}

void CommonEventsModel::setEditRoleData(int row, int column, const QVariant &value, Triple)
{
	Event *event = accessor.value(row);
	if (!event)
		return;

	switch (column)
	{
		case Event::ID: event->id = value.toInt(); break;
		case Event::NAME: event->name = value.toString(); updateDisplayRole(index(row, 1)); break;
		case Event::SWITCH_ID: event->switchId = value.toInt(); break;
		case Event::TRIGGER: event->trigger = value.toInt(); break;
		default: qDebug() << "CommonEventsModel::setDataFromMapper column" << column << "does not exist";
	}
}

