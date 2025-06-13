#include "clickable_label.hpp"
#include "iconset.hpp"
#include "images.hpp"

#include <QMouseEvent>
#include <QPainter>

void ClickableLabel::setIconIndex(int index)
{
	iconIndex = index;
	update();
}

void ClickableLabel::setIconMode(Mode mode, QPixmap pixmap)
{
	this->mode = mode;
	this->pixmap = pixmap;

	if (mode == FACES)
	{
		iconSize = 144;
		iconSetPitch = 4;
	}
}

void ClickableLabel::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)

	int y = iconIndex / iconSetPitch; // TODO: get icons count from IconSet
	int x = iconIndex % iconSetPitch;

	//QRect rect(x * width(), y * height(), width(), height());
	QRect rect(x * iconSize, y * iconSize, iconSize, iconSize);

	QPainter painter(this);
	painter.drawPixmap(QRect(0, 0, iconSize, iconSize), pixmap, rect);
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		event->accept();
		emit clicked();
	}

	event->ignore();
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		event->accept();
		emit doubleClicked();
	}

	event->ignore();
}
