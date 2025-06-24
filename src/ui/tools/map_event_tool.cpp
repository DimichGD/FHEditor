#include "map_event_tool.hpp"
#include "map_view.hpp"


/*MapEventTool::MapEventTool(QGraphicsScene *scene, QObject *parent): MapViewTool(parent)
{
	this->scene = scene;
	cursor = static_cast<QGraphicsRectItem *>(scene->items().at(0)); // TODO: sanity check
}*/

void MapEventTool::mousePress(QPoint pos)
{
	cursor->setPos(pos.x() * tileSize, pos.y() * tileSize);
}

void MapEventTool::mouseMove(QPoint pos)
{
	//
}

void MapEventTool::mouseRelease()
{
	//
}

void MapEventTool::mouseDoubleClick(QPoint pos)
{
	auto list = scene->items(QPoint(pos.x() * tileSize, pos.y() * tileSize));
	list.removeOne(cursor);

	if (list.size() > 0)
	{
		if (list.size() > 1)
		{
			qDebug() << "MapEventTool::mouseDoubleClick list.size() > 1";
			return;
		}

		auto item = static_cast<EventGraphicsItem *>(list.at(0));
		emit selectEvent(item->eventId());
	}
	else
	{
		MapEvent *event = tileMap->addNewEvent(pos.x(), pos.y());

		EventGraphicsItem *item = new EventGraphicsItem(event);
		item->setPos(pos.x() * tileSize, pos.y() * tileSize);
		item->setOpacity(EventGraphicsItem::drawFullItem ? 1.0f : 0.5f);
		scene->addItem(item);

		emit selectEvent(event->id);
	}
}
