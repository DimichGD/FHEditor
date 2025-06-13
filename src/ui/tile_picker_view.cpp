#include "tile_picker_view.hpp"
//#include <QApplication>
//#include <QStyle>
#include <QMouseEvent>
#include <QScrollBar>
#include <QGraphicsRectItem>

TilePickerScene::TilePickerScene(QObject *parent): QGraphicsScene(parent)
{
	cursorItem = new QGraphicsRectItem();
	addItem(cursorItem);

	QPen whitePen = QPen(QColorConstants::Magenta);
	whitePen.setWidth(2);
	whitePen.setJoinStyle(Qt::MiterJoin);
	whitePen.setCosmetic(true);
	cursorItem->setPen(whitePen);
}

void TilePickerScene::setBackgroundPixmap(QPixmap *pixmap)
{
	backgroundPixmap = pixmap;
	if (!pixmap)
		return;

	if (pixmap->width() == 768) // TODO: calc from width in tiles, assuming 8 is desired width
	{
		is16x16 = true;
		setSceneRect(0, 0, pixmap->width() / 2, pixmap->height() * 2);
	}
	else
	{
		setSceneRect(0, 0, pixmap->width(), pixmap->height());
	}
}

void TilePickerScene::setSelectionRect(const QRect &rect)
{
	cursorItem->setRect(rect.adjusted(2, 2, -2, -2).toRectF());
	cursorItem->show();
}

void TilePickerScene::clearSelection()
{
	cursorItem->hide();
}

void TilePickerScene::drawBackground(QPainter *painter, const QRectF &rect)
{
	if (backgroundPixmap)
	{
		if (!is16x16)
		{
			painter->drawPixmap(rect, *backgroundPixmap, rect);
			return;
		}

		float dx = 384;
		float dy = 768;
		QRectF rect1(0, 0, 384, 768);
		QRectF rect2(0, 768, 384, 768);
		QRectF intersection1 = rect.intersected(rect1);
		QRectF intersection2 = rect.intersected(rect2);

		painter->drawPixmap(intersection1, *backgroundPixmap, intersection1);
		painter->drawPixmap(intersection2, *backgroundPixmap, intersection2.adjusted(dx, -dy, dx, -dy));

		return;
	}

	QGraphicsScene::drawBackground(painter, rect);
}

// --------------------------------------------------------

TilePickerView::TilePickerView(QWidget *parent): QGraphicsView(parent)
{
	scene = new TilePickerScene(this);
	setScene(scene);
}

void TilePickerView::setBackgroundPixmap(TileSet::Set setIndex, int tileSize, QPixmap *pixmap)
{
	this->setIndex = setIndex;
	this->tileSize = tileSize;
	skipEvents = (!pixmap || pixmap->isNull());

	scene->setBackgroundPixmap(pixmap);
	scene->clearSelection();
	scene->update();

	if (pixmap)
		pixmapWidth = (pixmap->width() == 768) ? pixmap->width() / 2 : pixmap->width();
}

/*void TilePickerView::setTileSize(int size)
{
	tileSize = size;
}*/

void TilePickerView::selectRect(const QPoint &first, const QPoint &second)
{
	QPoint transformedFirst = mapToScene(first).toPoint();
	QPoint transformedSecond = mapToScene(second).toPoint();

	int x1 = transformedFirst.x() / tileSize;
	int y1 = transformedFirst.y() / tileSize;
	int x2 = transformedSecond.x() / tileSize;
	int y2 = transformedSecond.y() / tileSize;

	if (x2 < x1) std::swap(x1, x2);
	if (y2 < y1) std::swap(y1, y2);

	QRect rect(QPoint(x1, y1) * tileSize, QPoint(x2 + 1, y2 + 1) * tileSize - QPoint(1, 1));
	scene->setSelectionRect(rect);

	tilesSelectionRect = QRect(QPoint(x1, y1), QPoint(x2, y2));
	if (tilesSelectionRect != lastTilesSelectionRect)
	{
		lastTilesSelectionRect = tilesSelectionRect;
		scene->update();
	}
}

void TilePickerView::selectPoint(const QPoint &point)
{
	QPoint transformedPoint = mapToScene(point).toPoint();

	int x = transformedPoint.x() / tileSize;
	int y = transformedPoint.y() / tileSize;

	tilesSelectionRect.setX(x);
	tilesSelectionRect.setY(y);
	tilesSelectionRect.setWidth(1);
	tilesSelectionRect.setHeight(1);

	scene->setSelectionRect({ x * tileSize, y * tileSize, tileSize, tileSize });
	scene->update();
}

void TilePickerView::clearSelection()
{
	scene->clearSelection();
	scene->update();
}

void TilePickerView::selectTile(int tileId)
{
	tileId &= 0xFF;
	int x = tileId % 8;
	int y = tileId / 8;

	scene->setSelectionRect({ x * tileSize, y * tileSize, tileSize, tileSize });
	scene->update();
}

void TilePickerView::mousePressEvent(QMouseEvent *event)
{
	if (skipEvents)
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
	if (skipEvents)
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
	if (skipEvents)
	{
		event->ignore();
		return;
	}

	if (currentDragOp == SELECT)
	{
		if (tilesSelectionRect.width() * tilesSelectionRect.height() == 1)
			emit tileSelected(setIndex, tilesSelectionRect.left(), tilesSelectionRect.top());
		else
			emit multipleTilesSelected(setIndex, tilesSelectionRect);

		event->accept();
	}

	currentDragOp = NONE;
}

void TilePickerView::resizeEvent(QResizeEvent *event)
{
	if (pixmapWidth)
	{
		float scaleFactor = static_cast<float>(viewport()->width()) / pixmapWidth;
		setTransform(QTransform::fromScale(scaleFactor, scaleFactor));
	}

	QGraphicsView::resizeEvent(event);
}

