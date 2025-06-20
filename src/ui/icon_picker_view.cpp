#include "icon_picker_view.hpp"

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QMouseEvent>

IconPickerView::IconPickerView(QWidget *parent): QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);

	QPen whitePen = QPen(QColorConstants::Black);
	whitePen.setWidth(2);
	whitePen.setJoinStyle(Qt::MiterJoin);
	whitePen.setCosmetic(true);

	cursorItem = new QGraphicsRectItem();
	cursorItem->setPen(whitePen);
	scene->addItem(cursorItem);

	effect = new QGraphicsColorizeEffect(this);
	cursorItem->setGraphicsEffect(effect);

	QPropertyAnimation *animation = new QPropertyAnimation(effect, "color", this);
	animation->setDuration(1000);
	animation->setStartValue(QColor::fromRgb(0, 0, 0));
	animation->setKeyValueAt(0.5f, QColor::fromRgb(255, 255, 255));
	animation->setEndValue(QColor::fromRgb(0, 0, 0));
	animation->setLoopCount(-1);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void IconPickerView::setPixmap(QPixmap *pixmap, int tileSize)
{
	this->tileSize = tileSize;
	cursorItem->setRect(0, 0, tileSize, tileSize);

	scene->removeItem(cursorItem);
	scene->clear();
	scene->addItem(cursorItem);

	if (pixmap)
	{
		scene->setSceneRect(0, 0, pixmap->width(), pixmap->height());
		pixmapItem = scene->addPixmap(*pixmap);
		index = 0;
	}
	else
	{
		scene->setSceneRect(0, 0, tileSize, tileSize);
		index = -1;
	}

}

void IconPickerView::setPos(int x, int y)
{
	cursorItem->setPos(x * tileSize, y * tileSize);
}

void IconPickerView::clear()
{
	scene->removeItem(cursorItem);
	scene->clear();
	index = -1;
	pixmapItem = nullptr;
}

void IconPickerView::mousePressEvent(QMouseEvent *event)
{
	event->accept();
	if (!pixmapItem)
		return;

	if (event->button() == Qt::LeftButton)
	{
		QPoint point = mapToScene(event->position().toPoint()).toPoint();

		if (scene->sceneRect().contains(point))
		{
			int x = point.x() / tileSize;
			int y = point.y() / tileSize;
			//index = y * 16 + x;
			index = y * (pixmapItem->boundingRect().width() / tileSize) + x;

			setPos(x, y);
			emit tileClicked(x, y);
		}


		//return;
	}

	//event->ignore();
}

void IconPickerView::drawBackground(QPainter *painter, const QRectF &rect)
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

