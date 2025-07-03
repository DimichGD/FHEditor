#include "tile_picker_view.hpp"

#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsRectItem>


TilePickerView::TilePickerView(QWidget *parent): QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);

	cursorItem = new QGraphicsRectItem();
	scene->addItem(cursorItem);

	QPen whitePen = QPen(QColorConstants::Magenta);
	whitePen.setWidth(2);
	whitePen.setJoinStyle(Qt::MiterJoin);
	whitePen.setCosmetic(true);
	cursorItem->setPen(whitePen);
}

/*void TilePickerView::setBackgroundPixmap(TileSet::Set setIndex, int tileSize, QPixmap pixmap)
{
	this->setIndex = setIndex;
	this->tileSize = tileSize;

	pixmap = pixmap;
	if (!pixmap)
		return;

	cursorItem->setVisible(cursorSetIndex == setIndex);

	if (setIndex >= TileSet::B && setIndex <= TileSet::E)
		scene->setSceneRect(0, 0, pixmap.width() / 2, pixmap.height() * 2);
	else
		scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());

	scene->update();
}*/

void TilePickerView::setBackgroundPixmap(QPixmap pixmap, int tileSize, bool split)
{
	this->split = split;
	this->tileSize = tileSize;
	this->pixmap = pixmap;

	if (pixmap.isNull())
		return;

	if (split)
		scene->setSceneRect(0, 0, pixmap.width() / 2, pixmap.height() * 2);

	else
		scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());

	scene->update();
}

QGraphicsRectItem *TilePickerView::cursor()
{
	return cursorItem;
}


/*void TilePickerView::selectPoint(const QPoint &point)
{
	QPoint transformedPoint = mapToScene(point).toPoint();

	int maxHeight = scene->sceneRect().height() - 1;
	transformedPoint.ry() = std::min(transformedPoint.y(), maxHeight);

	int x = transformedPoint.x() / tileSize;
	int y = transformedPoint.y() / tileSize;

	tilesSelectionRect.setX(x);
	tilesSelectionRect.setY(y);
	tilesSelectionRect.setWidth(1);
	tilesSelectionRect.setHeight(1);

	QRect rect(x * tileSize, y * tileSize, tileSize, tileSize);
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorItem->show();
	scene->update();

	emit tileSelected(tilesSelectionRect.left(), tilesSelectionRect.top());
}*/

void TilePickerView::selectRect(const QPoint &first, const QPoint &second)
{
	QPoint transformedFirst = mapToScene(first).toPoint();
	QPoint transformedSecond = mapToScene(second).toPoint();

	int maxHeight = scene->sceneRect().height() - 1;
	transformedFirst.ry() = std::min(transformedFirst.y(), maxHeight);
	transformedSecond.ry() = std::min(transformedSecond.y(), maxHeight);

	int x1 = transformedFirst.x() / tileSize;
	int y1 = transformedFirst.y() / tileSize;
	int x2 = transformedSecond.x() / tileSize;
	int y2 = transformedSecond.y() / tileSize;

	if (x2 < x1) std::swap(x1, x2);
	if (y2 < y1) std::swap(y1, y2);

	QRect rect(QPoint(x1, y1) * tileSize, QPoint(x2 + 1, y2 + 1) * tileSize - QPoint(1, 1));
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorItem->show();

	tilesSelectionRect = QRect(QPoint(x1, y1), QPoint(x2, y2));
	scene->update();
	emit selected(tilesSelectionRect);
	/*if (tilesSelectionRect != lastTilesSelectionRect)
	{
		scene->update();
		lastTilesSelectionRect = tilesSelectionRect;

		emit selected(tilesSelectionRect);
	}*/
}



void TilePickerView::clearSelection()
{
	cursorItem->hide(); // FIXME: it does not clear selection
	scene->update();
}

/*void TilePickerView::selectTile(int tileId)
{
	tileId &= 0xFF;
	int x = tileId % 8;
	int y = tileId / 8;

	QRect rect( x * tileSize, y * tileSize, tileSize, tileSize );
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorSetIndex = setIndex;
	cursorItem->show();
	centerOn(cursorItem);
	scene->update();

	emit tileSelected(setIndex, x, y);
}*/

void TilePickerView::selectTile(int x, int y)
{
	QRect rect(x * tileSize, y * tileSize, tileSize, tileSize);
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	centerOn(cursorItem);
	scene->update();
	emit selected(QRect(x, y, 1, 1));
}

void TilePickerView::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsView::drawBackground(painter, rect);
	drawGrid(painter, rect);

	if (pixmap.isNull())
		return;

	if (!split)
	{
		painter->drawPixmap(rect, pixmap, rect);
		return;
	}

	float dx = pixmap.width() / 2;
	float dy = pixmap.height();
	QRectF rect1(0, 0,  dx, dy);
	QRectF rect2(0, dy, dx, dy);
	QRectF intersection1 = rect.intersected(rect1);
	QRectF intersection2 = rect.intersected(rect2);

	painter->drawPixmap(intersection1, pixmap, intersection1);
	painter->drawPixmap(intersection2, pixmap, intersection2.adjusted(dx, -dy, dx, -dy));
}

void TilePickerView::mousePressEvent(QMouseEvent *event)
{
	if (!pixmap)
	{
		event->ignore();
		return;
	}

	if (event->button() == Qt::LeftButton)
	{
		dragStart = event->position().toPoint();
		selectRect(dragStart, dragStart);
		//selectPoint(dragStart);

		currentDragOp = SELECT;
		event->accept();
	}

	if (event->button() == Qt::RightButton)
	{
		dragStart = event->position().toPoint();

		currentDragOp = SCROLL;
		event->accept();
	}
}

void TilePickerView::mouseMoveEvent(QMouseEvent *event)
{
	if (!pixmap)
	{
		event->ignore();
		return;
	}

	if (currentDragOp == SELECT)
	{
		QPoint pos = event->position().toPoint();
		pos.rx() = std::min(viewport()->width()  - 1, std::max(1, pos.x()));
		pos.ry() = std::min(viewport()->height() - 1, std::max(1, pos.y()));
		selectRect(dragStart, pos);

		event->accept();
	}

	if (currentDragOp == SCROLL)
	{
		QPoint pos = event->position().toPoint();
		verticalScrollBar()->setValue(verticalScrollBar()->value() - (pos.y() - dragStart.y()));
		dragStart = pos;

		event->accept();
	}

	event->ignore();
}

void TilePickerView::mouseReleaseEvent(QMouseEvent *event)
{
	if (pixmap.isNull())
	{
		event->ignore();
		return;
	}

	currentDragOp = NONE;
	event->accept();
}

void TilePickerView::resizeEvent(QResizeEvent *event)
{
	if (!pixmap.isNull())
	{
		int tileSetWidth = tileSize * 8;
		float scaleFactor = static_cast<float>(viewport()->width()) / tileSetWidth;
		setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
	}

	QGraphicsView::resizeEvent(event);
}

void TilePickerView::drawGrid(QPainter *painter, const QRectF &rect)
{
	painter->setPen(QColor::fromRgb(220, 220, 220));
	int gridSize = tileSize / 2;
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

