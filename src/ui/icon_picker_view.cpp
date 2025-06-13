#include "icon_picker_view.hpp"

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QMouseEvent>

IconPickerView::IconPickerView(QWidget *parent): QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);
}

void IconPickerView::setPixmap(const QPixmap &pixmap)
{
	if (scene->items().contains(cursor))
			scene->removeItem(cursor);

	scene->clear();
	scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
	pixmapItem = scene->addPixmap(pixmap);
	scene->addItem(cursor);
}

void IconPickerView::setTileSize(int size)
{
	tileSize = size;

	QString filename = QString("frame%1.png").arg(tileSize);
	cursor = new QGraphicsPixmapItem(QPixmap(filename));

	effect = new QGraphicsColorizeEffect(this);
	cursor->setGraphicsEffect(effect);

	QPropertyAnimation *animation = new QPropertyAnimation(effect, "color", this);
	animation->setDuration(1000);
	animation->setStartValue(QColor::fromRgb(0, 0, 0));
	animation->setKeyValueAt(0.5f, QColor::fromRgb(255, 255, 255));
	animation->setEndValue(QColor::fromRgb(0, 0, 0));
	animation->setLoopCount(-1);
	animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void IconPickerView::setPos(int x, int y)
{
	cursor->setPos(x * tileSize, y * tileSize);
}

void IconPickerView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint point = mapToScene(event->position().toPoint()).toPoint();

		if (scene->sceneRect().contains(point))
		{
			int x = point.x() / tileSize;
			int y = point.y() / tileSize;
			index = y * 16 + x;

			setPos(x, y);
			emit tileClicked(x, y);
		}

		event->accept();
		return;
	}

	event->ignore();
}

void IconPickerView::drawBackground(QPainter *painter, const QRectF &rect)
{
	painter->setPen(QColor::fromRgb(220, 220, 220));
	int mGridSize = 16;
	QRect r = rect.toRect();

	int xmin = r.left() - r.left() % mGridSize - mGridSize;
	int ymin = r.top() - r.top() % mGridSize - mGridSize;
	int xmax = r.right() - r.right() % mGridSize + mGridSize;
	int ymax = r.bottom() - r.bottom() % mGridSize + mGridSize;

	for (int x = xmin; x <= xmax; x += mGridSize)
		painter->drawLine(x, r.top(), x, r.bottom());

	for (int y = ymin; y <= ymax; y+= mGridSize)
		painter->drawLine(r.left(), y, r.right(), y);
}

