#pragma once
#include <QGraphicsView>
#include <QGraphicsColorizeEffect>

class IconPickerView: public QGraphicsView
{
	Q_OBJECT

public:
	IconPickerView(QWidget *parent = nullptr);
	void setPixmap(const QPixmap &pixmap);
	void setTileSize(int size);
	void setPos(int x, int y);
	int index = -1; // TODO: make private

signals:
	void tileClicked(int x, int y);

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	int tileSize = 32; // TODO: can't do in ctor, make setter

	QGraphicsScene *scene = nullptr;
	QGraphicsPixmapItem *pixmapItem = nullptr;
	QGraphicsPixmapItem *cursor = nullptr;
	QGraphicsColorizeEffect *effect = nullptr;
};
