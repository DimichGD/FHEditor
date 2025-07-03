#pragma once
#include "tileset.hpp"
#include <QGraphicsView>


class TilePickerView: public QGraphicsView
{
	Q_OBJECT

public:
	TilePickerView(QWidget *parent = nullptr);
	void setBackgroundPixmap(TileSet::Set setIndex, int tileSize, QPixmap pixmap);
	void setBackgroundPixmap(QPixmap pixmap, int tileSize, bool split);
	QGraphicsRectItem *cursor();

	void selectPoint(const QPoint &point);
	void selectRect(const QPoint &first, const QPoint &second);
	void clearSelection();

public slots:
	void selectTile(int tileId);

signals:
	void tileSelected(TileSet::Set setIndex, int x, int y);
	void multipleTilesSelected(TileSet::Set setIndex, const QRect &rect);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private:
	enum DragOp { NONE, SCROLL, SELECT };
	DragOp currentDragOp = NONE;
	QPoint dragStart {};

	//bool skipEvents = true;
	int tileSize = 0;
	//int pixmapWidth = 0;

	TileSet::Set setIndex = TileSet::COUNT;
	TileSet::Set cursorSetIndex = TileSet::COUNT;
	QRect tilesSelectionRect {};
	QRect lastTilesSelectionRect {};

	QGraphicsScene *scene = nullptr;
	QPixmap backgroundPixmap;
	QGraphicsRectItem *cursorItem = nullptr;
};

