#pragma once
#include "image.hpp"
#include <QLabel>

class QMouseEvent;

class ClickableLabel: public QLabel
{
	Q_OBJECT

public:
	enum Mode
	{
		ICON_SET, FACES, CHARACTER,
	};

	ClickableLabel(QWidget *parent = nullptr): QLabel(parent) {}
	void setIconIndex(int index);
	void setIconMode(Mode mode, QPixmap *pixmap);
	void setIconImage(const Image &image);
	void paintEvent(QPaintEvent *event) override;

signals:
	void clicked();
	void doubleClicked();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	QRect rect;
	int iconIndex = 0;

	QPixmap *pixmap = nullptr;
	Mode mode;
	//int iconSize = 32;
	QSize iconSize { 32, 32 };
	int iconSetPitch = 16;
};

