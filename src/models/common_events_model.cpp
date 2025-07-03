#include "common_events_model.hpp"
#include "database.hpp"

CommonEventsModel::CommonEventsModel(QObject *parent)
	: BaseModel2(&accessor, parent), accessor(Database::Get()->accessor<Event>()) {}

Event *CommonEventsModel::commonEvent(int row)
{
	return accessor.value(row + 1);
}

QVariant CommonEventsModel::data(int id, int column) const
{
	const Event *event = accessor.value(id);

	switch (column)
	{
		case Event::ID: return event->id;
		case Event::NAME: return event->name;
		case Event::SWITCH_ID: return event->switchId;
		case Event::TRIGGER: return event->trigger;
		default: qDebug() << "CommonEventsModel::data column" << column << "does not exist";
	}

	return QVariant();
}

void CommonEventsModel::setData(int id, int column, const QVariant &value)
{
	Event *event = accessor.value(id);

	switch (column)
	{
		case Event::ID: event->id = value.toInt(); break;
		case Event::NAME: event->name = value.toString(); break;
		case Event::SWITCH_ID: event->switchId = value.toInt(); break;
		case Event::TRIGGER: event->trigger = value.toInt(); break;
		default: qDebug() << "CommonEventsModel::setData column" << column << "does not exist";
	}
}

