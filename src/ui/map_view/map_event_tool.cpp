#include "map_event_tool.hpp"
#include "map_view.hpp"


/*MapEventTool::MapEventTool(QGraphicsScene *scene, QObject *parent): MapViewTool(parent)
{
	this->scene = scene;
	cursor = static_cast<QGraphicsRectItem *>(scene->items().at(0)); // TODO: sanity check
}*/

void MapEventTool::mousePress(int x, int y)
{
	cursor->setPos(x * tileSize, y * tileSize);
}

void MapEventTool::mouseMove(int x, int y)
{
	//
}

void MapEventTool::mouseRelease()
{
	//
}

void MapEventTool::mouseDoubleClick(int x, int y)
{
	auto list = scene->items(QPoint(x * 48, y * 48));
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
		MapEvent *event = tileMap->addNewEvent(x, y);

		EventGraphicsItem *item = new EventGraphicsItem(event);
		item->setPos(x * tileSize, y * tileSize);
		item->setOpacity(EventGraphicsItem::drawFullItem ? 1.0f : 0.5f);
		scene->addItem(item);

		emit selectEvent(event->id);
	}
}
