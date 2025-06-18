#include "map_view.hpp"

#include <QFile>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsPixmapItem>

bool EventGraphicsItem::drawFullItem = false;

EventGraphicsItem::EventGraphicsItem(MapEvent *event, QGraphicsItem *parent): QGraphicsItem(parent)
{
	this->event = event;
	setOpacity(0.5f);
}

QRectF EventGraphicsItem::boundingRect() const
{
	return { 0, 0, 48, 48 };
}

void EventGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//QBrush brush(QColorConstants::White);
	QPen pen(QColorConstants::White);
	pen.setCosmetic(true);
	painter->setPen(pen);
	painter->drawRect(2, 2, 44, 44);

	if (drawFullItem)
	{
		QBrush brush(QColor::fromRgb(0, 0, 0, 128));
		painter->fillRect(QRect(3, 3, 43, 43), brush);
		//painter->setFont(QFont("Noto Sans Mono", 8));
		//painter->drawText(QPoint(5, 15), event->name);
	}
}


MapView::MapView(QWidget *parent): QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);
}

MapView::~MapView()
{
	//
}

void MapView::load(Map *map, TileMap *tileMap)
{
	this->tileMap = tileMap;

	eventItemMap.clear();
	scene->clear();
	scene->setSceneRect(0, 0, tileMap->width() * tileSize, tileMap->height() * tileSize);

	for (auto &eventOptional: map->events)
	{
		if (!eventOptional.has_value())
			continue;

		MapEvent &event = eventOptional.value();
		EventGraphicsItem *item = new EventGraphicsItem(&event);
		item->setPos(event.x * tileSize, event.y * tileSize);
		scene->addItem(item);
		eventItemMap[event.y * tileMap->width() + event.x] = item;
	}

	QPen pen(QColorConstants::White);
	pen.setWidth(2);
	pen.setCosmetic(true);
	pen.setJoinStyle(Qt::MiterJoin);
	cursor = new QGraphicsRectItem(QRect(0, 0, tileSize + 1, tileSize + 1));
	cursor->setPen(pen);
	scene->addItem(cursor);

	setEnabled(true);
	centerOn(scene->sceneRect().center());
	repaint();
	//currentMap = map;
}

void MapView::clear()
{
	//for (auto &group: groups)
	//	group.items.clear();

	//tilesets.clear();
	scene->clear();
	resetCachedContent();

	//tiles.clear();
	setTransform(QTransform());
}

void MapView::layersToggled(int id, bool toggled)
{
	/*if (scene->items().isEmpty())
		return;

	if (toggled)
	{
		for (auto item: groups[id].items)
			item->show();
	}
	else
	{
		for (auto item: groups[id].items)
			item->hide();
	}*/
}

void MapView::setCurrentMode(int mode)
{
	if (mode == currentMode)
		return;

	currentMode = Mode(mode);
	bool flag = (currentMode == EVENTS);
	EventGraphicsItem::drawFullItem = flag;

	for (auto [_, value]: eventItemMap)
	{
		value->setOpacity(flag ? 1.0f : 0.5f);
		value->update();
	}

	currentOp = PAINT_SINGLE;
	cursor->setRect(0, 0, tileSize, tileSize);
}


void MapView::setCurrentTileSingle(TileSet::Set setIndex, int x, int y)
{
	currentTileInfo = tileMap->tileItemInfo(x, y, setIndex);
	currentOp = PAINT_SINGLE;
	cursor->setRect(0, 0, tileSize, tileSize);
	if (setIndex >= TileSet::B && setIndex <= TileSet::E && x == 0 && y == 0)
		currentTileInfo.pixmap = nullptr;
}

void MapView::setCurrentTileMultiple(TileSet::Set setIndex, const QRect &rect)
{
	QList<TileItemInfo> tileInfos;
	tileInfos.reserve(rect.width() * rect.height());
	for (int y = rect.top(); y <= rect.bottom(); y++)
	{
		for (int x = rect.left(); x <= rect.right(); x++)
		{
			tileInfos.append(tileMap->tileItemInfo(x, y, setIndex));
		}
	}

	currentMultipleTileSize = rect.size();
	currentMultipleTileInfoList = tileInfos;
	currentOp = PAINT_MULTIPLE;
	cursor->setRect(0, 0, rect.size().width() * tileSize, rect.size().height() * tileSize);
}


void MapView::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsView::drawBackground(painter, rect);
	if (!tileMap)
		return;

	QRectF rect2 = rect.intersected(scene->sceneRect());

	int x1 = int(rect2.left()) / tileSize;
	int y1 = int(rect2.top()) / tileSize;
	int x2 = int(rect2.right() - 1.0f) / tileSize;
	int y2 = int(rect2.bottom() - 1.0f) / tileSize;

	for (int layer = 0; layer < 5; layer++)
	{
		for (int y = y1; y <= y2; y++)
		{
			for (int x = x1; x <= x2; x++)
			{
				int tileId = tileMap->tileId(x, y, layer);

				if (layer != 0 && (tileId & 0xFF) == 0)
					continue;

				if (layer == 0 && tileId == 0)
					continue;

				TileItemInfo info = tileMap->tileItemInfo(tileId);
				QRect dstRect(x * tileSize, y * tileSize, tileSize, tileSize);
				painter->drawPixmap(dstRect, *info.pixmap, info.rect);
			}
		}
	}
}


void MapView::wheelEvent(QWheelEvent *event)
{
	if (scene->items().isEmpty())
		return;

	scaleValue *= (event->angleDelta().y() > 0.0f) ? 1.125f : 0.875f;
	setTransform(QTransform::fromScale(scaleValue, scaleValue));
	event->accept();
}

void MapView::mousePressEvent(QMouseEvent *event)
{
	event->accept();

	if (event->button() == Qt::RightButton)
	{
		scrollStart = event->position().toPoint();
		isScrolling = true;
		return;
	}

	QPoint pos = mapToScene(event->position().toPoint()).toPoint();
	pos.rx() = pos.x() / tileSize;
	pos.ry() = pos.y() / tileSize;

	if (event->button() != Qt::LeftButton)
		return;

	if (currentMode == EVENTS)
	{
		//

		return;
	}

	if (currentMode == TILES && currentOp == PAINT_SINGLE)
	{
		if (currentTileInfo.id < 0)
			return;

		tileMap->putTile(pos.x(), pos.y(), currentLayer, currentTileInfo.id);
		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize, tileSize, tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);

		isPainting = true;
		paintingStart = pos;
	}

	if (currentMode == TILES && currentOp == PAINT_MULTIPLE)
	{
		int index = 0;
		for (int y = pos.y(); y < pos.y() + currentMultipleTileSize.height(); y++)
		{
			for (int x = pos.x(); x < pos.x() + currentMultipleTileSize.width(); x++)
			{
				tileMap->putTile(x, y, currentLayer, currentMultipleTileInfoList[index].id);
				++index;
			}
		}

		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize,
			currentMultipleTileSize.width() * tileSize, currentMultipleTileSize.height() * tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);

		isPainting = true;
		paintingStart = pos;
	}

	if (currentMode == PICKER)
	{
		for (int i = 5; i >= 0; i--)
		{
			int tileId = tileMap->tileId(pos.x(), pos.y(), i);
			if (tileId != 0)
			{
				emit pickTile(tileId);
				break;
			}
		}
	}

	//lastTilePos = pos;
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{
	event->accept();

	if (isScrolling)
	{
		QPoint pos = event->position().toPoint();
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (pos.x() - scrollStart.x()));
		verticalScrollBar()->setValue(verticalScrollBar()->value() - (pos.y() - scrollStart.y()));
		scrollStart = pos;

		if (cursor)
			cursor->update();

		return;
	}

	QPoint pos = mapToScene(event->position().toPoint()).toPoint();
	pos.rx() = pos.x() / tileSize;
	pos.ry() = pos.y() / tileSize;

	if (pos == lastTilePos)
		return;

	if (cursor)
	{
		pos.rx() = std::min(tileMap->width() - 1, std::max(0, pos.x()));
		pos.ry() = std::min(tileMap->height() - 1, std::max(0, pos.y()));

		cursor->setPos(pos.x() * tileSize, pos.y() * tileSize);
		cursor->update();
	}

	if (isPainting && currentOp == PAINT_SINGLE)
	{
		tileMap->putTile(pos.x(), pos.y(), currentLayer, currentTileInfo.id);
		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize, tileSize, tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
	}

	if (isPainting && currentOp == PAINT_MULTIPLE)
	{
		int w = currentMultipleTileSize.width();
		int h = currentMultipleTileSize.height();
		for (int y = pos.y(); y < pos.y() + h; y++)
		{
			for (int x = pos.x(); x < pos.x() + w; x++)
			{
				int index = (std::abs(y - paintingStart.y()) % h) * w
						+ (std::abs(x - paintingStart.x()) % w);
				tileMap->putTile(x, y, currentLayer, currentMultipleTileInfoList[index].id);
				++index;
			}
		}

		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize,
			currentMultipleTileSize.width() * tileSize,
			currentMultipleTileSize.height() * tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
	}

	lastTilePos = pos;
}


void MapView::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();

	isPainting = false;
	isScrolling = false;
}

void MapView::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->accept();

	if (currentMode != EVENTS)
		return;

	int index = lastTilePos.y() * tileMap->width() + lastTilePos.x();
	auto it = eventItemMap.find(index);
	if (it != eventItemMap.end())
	{
		emit editEvent(it->second->eventId());
	}
	else
	{
		emit newEvent(lastTilePos.x(), lastTilePos.y());
	}
}

