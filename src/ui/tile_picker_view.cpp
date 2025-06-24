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

void TilePickerView::setBackgroundPixmap(TileSet::Set setIndex, int tileSize, QPixmap *pixmap)
{
	this->setIndex = setIndex;
	this->tileSize = tileSize;

	backgroundPixmap = pixmap;
	if (!pixmap)
		return;

	cursorItem->setVisible(cursorSetIndex == setIndex);

	if (setIndex >= TileSet::B && setIndex <= TileSet::E)
		scene->setSceneRect(0, 0, pixmap->width() / 2, pixmap->height() * 2);
	else
		scene->setSceneRect(0, 0, pixmap->width(), pixmap->height());

	scene->update();
}


void TilePickerView::selectPoint(const QPoint &point)
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

	QRect rect( x * tileSize, y * tileSize, tileSize, tileSize );
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorSetIndex = setIndex;
	cursorItem->show();
	scene->update();

	emit tileSelected(setIndex, tilesSelectionRect.left(), tilesSelectionRect.top());
}

void TilePickerView::selectRect(const QPoint &first, const QPoint &second)
{
	QPoint transformedFirst = mapToScene(first).toPoint();
	QPoint transformedSecond = mapToScene(second).toPoint();

	int maxHeight = scene->sceneRect().height() - 1;
	transformedFirst.ry() = std::min(transformedFirst.y(), maxHeight);
	transformedSecond.ry() = std::min(transformedSecond.y(), maxHeight);

	/*if (transformedFirst.y() >= scene->sceneRect().height())
		transformedFirst.setY(scene->sceneRect().height() - 1);

	if (transformedSecond.y() >= scene->sceneRect().height())
		transformedSecond.setY(scene->sceneRect().height() - 1);*/

	int x1 = transformedFirst.x() / tileSize;
	int y1 = transformedFirst.y() / tileSize;
	int x2 = transformedSecond.x() / tileSize;
	int y2 = transformedSecond.y() / tileSize;

	if (x2 < x1) std::swap(x1, x2);
	if (y2 < y1) std::swap(y1, y2);

	QRect rect(QPoint(x1, y1) * tileSize, QPoint(x2 + 1, y2 + 1) * tileSize - QPoint(1, 1));
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorSetIndex = setIndex;
	cursorItem->show();

	tilesSelectionRect = QRect(QPoint(x1, y1), QPoint(x2, y2));
	if (tilesSelectionRect != lastTilesSelectionRect)
	{
		scene->update();
		lastTilesSelectionRect = tilesSelectionRect;

		emit multipleTilesSelected(setIndex, tilesSelectionRect);
	}
}



void TilePickerView::clearSelection()
{
	cursorItem->hide(); // FIXME: it does not clear selection
	scene->update();
}

void TilePickerView::selectTile(int tileId)
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
}

void TilePickerView::drawBackground(QPainter *painter, const QRectF &rect)
{
	QGraphicsView::drawBackground(painter, rect);

	if (!backgroundPixmap)
		return;

	if (setIndex == TileSet::A5)
	{
		painter->drawPixmap(rect, *backgroundPixmap, rect);
		return;
	}

	float dx = 384; // FIXME: remove hardcoded variables
	float dy = 768;
	QRectF rect1(0, 0, 384, 768);
	QRectF rect2(0, 768, 384, 768);
	QRectF intersection1 = rect.intersected(rect1);
	QRectF intersection2 = rect.intersected(rect2);

	painter->drawPixmap(intersection1, *backgroundPixmap, intersection1);
	painter->drawPixmap(intersection2, *backgroundPixmap, intersection2.adjusted(dx, -dy, dx, -dy));

	return;
}

void TilePickerView::mousePressEvent(QMouseEvent *event)
{
	if (!backgroundPixmap)
	{
		event->ignore();
		return;
	}

	if (event->button() == Qt::LeftButton)
	{
		dragStart = event->position().toPoint();
		selectPoint(event->position().toPoint());

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
	if (!backgroundPixmap)
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
	if (!backgroundPixmap)
	{
		event->ignore();
		return;
	}

	currentDragOp = NONE;
	event->accept();
}

void TilePickerView::resizeEvent(QResizeEvent *event)
{
	if (backgroundPixmap)
	{
		float scaleFactor = static_cast<float>(viewport()->width()) / 384; // FIXME: remove hardcoded variables
		setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
	}

	QGraphicsView::resizeEvent(event);
}

