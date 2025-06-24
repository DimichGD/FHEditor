#include "map_view.hpp"
#include "settings.hpp"
#include "images.hpp"

#include <QFile>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QtConcurrentRun>

bool EventGraphicsItem::drawFullItem = false;

EventGraphicsItem::EventGraphicsItem(MapEvent *event, QGraphicsItem *parent): QGraphicsItem(parent)
{
	this->event = event;
	//id = eventId;
	setOpacity(0.5f);
}

QRectF EventGraphicsItem::boundingRect() const
{
	return bounds;
}

QPainterPath EventGraphicsItem::shape() const
{
	QPainterPath path;
	path.addRect({ 0, 0, 48, 48 });
	return path;
}

void EventGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	//QBrush brush(QColorConstants::White);
	//if (!pixmap)
	{
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

	if (pixmap)
	{
		painter->drawPixmap(bounds, *pixmap, pixmapRect);

		/*QPen pen(QColorConstants::White);
		pen.setCosmetic(true);
		painter->setPen(pen);
		painter->drawRect(bounds.adjusted(1, 1, -2, -2));*/
	}
}


MapView::MapView(QWidget *parent): QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);

	QPen pen(QColorConstants::White);
	pen.setWidth(2);
	pen.setCosmetic(true);
	pen.setJoinStyle(Qt::MiterJoin);
	cursor = new QGraphicsRectItem(QRect(2, 2, tileSize - 3, tileSize - 3));
	cursor->setPen(pen);
	cursor->setData(0, "cursor");
	cursor->setAcceptedMouseButtons(Qt::NoButton);
	cursor->setZValue(100.0f);
	scene->addItem(cursor);
}

MapView::~MapView()
{
	//
}

void MapView::load(TileMap *tileMap)
{
	clear();
	this->tileMap = tileMap;

	scene->setSceneRect(0, 0, tileMap->width() * tileSize, tileMap->height() * tileSize);

	for (auto &eventOptional: *tileMap->events())
	{
		if (!eventOptional.has_value())
			continue;

		MapEvent &event = eventOptional.value();
		EventGraphicsItem *item = new EventGraphicsItem(&event);
		item->setPos(event.x * tileSize, event.y * tileSize);
		item->setOpacity(EventGraphicsItem::drawFullItem ? 1.0f : 0.5f);
		scene->addItem(item);
		eventItemMap[event.id] = item;
	}


	setEnabled(true);
	centerOn(scene->sceneRect().center());
	repaint();
	//currentMap = map;

	auto promise = QtConcurrent::run(&MapView::startAsyncLoad, this);
	promise.then(this, [this](){ completeAsyncLoad(); });
}

void MapView::clear()
{
	//for (auto &group: groups)
	//	group.items.clear();
	tileMap = nullptr;

	for (auto it: eventItemMap)
		delete it.second;

	//tilesets.clear();
	eventItemMap.clear();
	//scene->clear();
	resetCachedContent();

	//tiles.clear();
	setTransform(QTransform());
}


void MapView::setCurrentMode(int mode)
{
	Settings::Get()->mapToolIndex = mode;

	bool flag = (mode == 1);
	EventGraphicsItem::drawFullItem = flag;

	for (auto [_, value]: eventItemMap)
	{
		value->setOpacity(flag ? 1.0f : 0.5f);
		value->update();
	}

	//cursor->setRect(0, 0, tileSize, tileSize);
	cursor->setRect(QRect(2, 2, tileSize - 3, tileSize - 3));
}


/*void MapView::addNewEvent(MapEvent event)
{
	EventGraphicsItem *item = new EventGraphicsItem(event.id);
	item->setPos(event.x * tileSize, event.y * tileSize);
	item->setOpacity(EventGraphicsItem::drawFullItem ? 1.0f : 0.5f);
	scene->addItem(item);
	eventItemMap[event.id] = item;
}*/


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
				if (info.pixmap)
				{
					QRect dstRect(x * tileSize, y * tileSize, tileSize, tileSize);
					painter->drawPixmap(dstRect, *info.pixmap, info.rect);
				}
				else
				{
					// FIXME: pixmap is null sometimes
				}
			}
		}
	}
}

void MapView::drawForeground(QPainter *painter, const QRectF &rect)
{
	painter->setPen(QColorConstants::Black);
	int gridSize = tileSize;
	QRect r = rect.toRect();

	int xmin = r.left() - r.left() % gridSize - gridSize;
	int ymin = r.top() - r.top() % gridSize - gridSize;
	int xmax = r.right() - r.right() % gridSize + gridSize;
	int ymax = r.bottom() - r.bottom() % gridSize + gridSize;

	for (int x = xmin; x <= xmax; x += gridSize)
		painter->drawLine(x, r.top(), x, r.bottom());

	for (int y = ymin; y <= ymax; y+= gridSize)
		painter->drawLine(r.left(), y, r.right(), y);
}


void MapView::wheelEvent(QWheelEvent *event)
{
	scaleValue *= (event->angleDelta().y() > 0.0f) ? 1.125f : 0.875f;
	setTransform(QTransform::fromScale(scaleValue, scaleValue));
	event->accept();
}

void MapView::mousePressEvent(QMouseEvent *event)
{
	event->accept();

	if (event->button() == Qt::RightButton)
	{
		scrollStart = mapToGlobal(event->position().toPoint());
		isScrolling = true;
		return;
	}

	if (event->button() != Qt::LeftButton)
		return;

	QPoint pos = mapToScene(event->position().toPoint()).toPoint();
	if (!scene->sceneRect().contains(pos))
		return;

	pos.rx() = pos.x() / tileSize;
	pos.ry() = pos.y() / tileSize;
	//lastTilePos = pos; // FIXME: do i need this?

	currentTool->mousePress(pos.x(), pos.y());
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{
	event->accept();

	if (isScrolling)
	{
		QPoint pos = mapToGlobal(event->position().toPoint());
		horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (pos.x() - scrollStart.x()));
		verticalScrollBar()->setValue(verticalScrollBar()->value() - (pos.y() - scrollStart.y()));
		scrollStart = pos;

		cursor->update();

		QRect resolution = QApplication::primaryScreen()->geometry();
		if (pos.y() >= resolution.bottom() - 1)
		{
			QCursor::setPos(pos.x(), resolution.top() + 10);
			scrollStart.ry() -= (resolution.height() - 10);
		}
		else if (pos.y() <= resolution.top() + 1)
		{
			QCursor::setPos(pos.x(), resolution.bottom() - 10);
			scrollStart.ry() += (resolution.height() - 10);
		}

		if (pos.x() == resolution.right() - 1)
		{
			QCursor::setPos(resolution.left() + 10, pos.y());
			scrollStart.rx() -= (resolution.width() - 10);
		}
		else if (pos.x() <= resolution.left() + 1)
		{
			QCursor::setPos(resolution.right() - 10, pos.y());
			scrollStart.rx() += (resolution.width() - 10);
		}

		return;
	}

	QPoint pos = mapToScene(event->position().toPoint()).toPoint();
	if (!scene->sceneRect().contains(pos))
		return;

	pos.rx() = pos.x() / tileSize;
	pos.ry() = pos.y() / tileSize;

	if (pos == lastTilePos)
		return;

	currentTool->mouseMove(pos.x(), pos.y());

	lastTilePos = pos;
}


void MapView::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();

	currentTool->mouseRelease();

	isScrolling = false;
}

void MapView::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->accept();

	QPoint pos = mapToScene(event->position().toPoint()).toPoint();
	if (!scene->sceneRect().contains(pos))
		return;

	pos.rx() = pos.x() / tileSize;
	pos.ry() = pos.y() / tileSize;

	currentTool->mouseDoubleClick(pos.x(), pos.y());
}

void MapView::startAsyncLoad()
{
	for (auto &eventOptional: *tileMap->events())
	{
		if (!eventOptional.has_value())
			continue;

		MapEvent &event = eventOptional.value();
		Image *image = &event.pages[0].image;
		if (!image->characterName.isEmpty())
			Images::Get()->loadImage("characters/" + image->characterName);
	}
}

void MapView::completeAsyncLoad()
{
	for (auto it: eventItemMap)
	{
		MapEvent &event = tileMap->events()->at(it.first).value();
		Image *image = &event.pages[0].image;
		if (!image->characterName.isEmpty())
		{
			QPixmap *pixmap = Images::Get()->loadImage("characters/" + image->characterName);
			int width = pixmap->width() / 12;
			int height = pixmap->height() / 8;

			if (image->characterName[0] == '$')
			{
				width = pixmap->width() / 3;
				height = pixmap->height() / 4;
			}

			int x = width * (image->characterIndex * 3 + image->pattern);
			int y = height * (image->direction / 2 - 1);

			if (x >= pixmap->width())
			{
				x -= pixmap->width();
				y += height * 4;
			}

			int cX = (width - 48) / 2;
			int cY = (height - 48);

			if (image->characterName[0] != '!')
				cY += 6;

			QRect bounds = { -cX, -cY, width, height };
			QRect pixmapRect = { x, y, width, height };

			it.second->updatePixmap(bounds, pixmap, pixmapRect);
		}

		if (event.pages[0].image.tileId)
		{
			TileItemInfo info = tileMap->tileItemInfo(event.pages[0].image.tileId);
			it.second->updatePixmap({ 0, 0, 48, 48 }, info.pixmap, info.rect);
		}

	}

	scene->invalidate();
}

