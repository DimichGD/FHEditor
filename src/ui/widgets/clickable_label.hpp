#pragma once
#include <QLabel>

class QMouseEvent;

class ClickableLabel: public QLabel
{
	Q_OBJECT

public:
	enum Mode
	{
		ICON_SET, FACES,
	};

	ClickableLabel(QWidget *parent = nullptr): QLabel(parent) {}
	void setIconIndex(int index);
	void setIconMode(Mode mode, QPixmap pixmap);
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

	QPixmap pixmap;
	Mode mode;
	int iconSize = 32;
	int iconSetPitch = 16;
};

