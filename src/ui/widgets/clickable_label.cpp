#include "clickable_label.hpp"
//#include "iconset.hpp"
#include "images.hpp"

#include <QMouseEvent>
#include <QPainter>

void ClickableLabel::setIconIndex(int index)
{
	iconIndex = index;
	update();
}

void ClickableLabel::setIconMode(Mode mode, QPixmap *pixmap)
{
	this->mode = mode;
	this->pixmap = pixmap;

	if (mode == FACES)
	{
		iconSize = { 144, 144 };
		iconSetPitch = 4;
	}
}

void ClickableLabel::setIconMode(Mode mode, const QString &filename)
{
	this->mode = mode;
	if (mode == CHARACTER)
	{
		pixmap = Images::Get()->loadImage("characters/" + filename);
		if (filename[0] == '$')
		{
			iconSize.setWidth(pixmap->width() / 3);
			iconSize.setHeight(pixmap->height() / 4);
			iconSetPitch = 3;
		}
		else
		{
			iconSize.setWidth(pixmap->width() / 12);
			iconSize.setHeight(pixmap->height() / 8);
			iconSetPitch = 12;
		}
	}
}

void ClickableLabel::paintEvent(QPaintEvent *event)
{
	int y = iconIndex / iconSetPitch; // TODO: get icons count from IconSet
	int x = iconIndex % iconSetPitch;

	//QRect rect(x * width(), y * height(), width(), height());
	QRect rect(x * iconSize.width(), y * iconSize.height(), iconSize.width(), iconSize.height());

	QPainter painter(this);

	if (pixmap)
		painter.drawPixmap(QRect(0, 0, iconSize.width(), iconSize.height()), *pixmap, rect);
	else
		QLabel::paintEvent(event);
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
