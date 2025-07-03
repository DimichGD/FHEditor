#pragma once
#include "tileset.hpp"
#include <QGraphicsView>


class TilePickerView: public QGraphicsView
{
	Q_OBJECT

public:
	TilePickerView(QWidget *parent = nullptr);
	//void setBackgroundPixmap(TileSet::Set setIndex, int tileSize, QPixmap pixmap);
	void setBackgroundPixmap(QPixmap pixmap, int tileSize, bool split);
	void clearSelection();
	QGraphicsRectItem *cursor();

public slots:
	//void selectTile(int tileId);
	void selectTile(int x, int y);

signals:
	void selected(const QRect &rect);
	//void tileSelected(int x, int y);
	//void multipleTilesSelected(const QRect &rect);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private:
	//void selectPoint(const QPoint &point);
	void selectRect(const QPoint &first, const QPoint &second);
	void drawGrid(QPainter *painter, const QRectF &rect);

private:
	enum DragOp { NONE, SCROLL, SELECT };
	DragOp currentDragOp = NONE;
	QPoint dragStart {};

	//bool skipEvents = true;
	bool split = false;
	int tileSize = 0;
	//int pixmapWidth = 0;

	//TileSet::Set setIndex = TileSet::COUNT;
	//TileSet::Set cursorSetIndex = TileSet::COUNT;
	QRect tilesSelectionRect {};
	QRect lastTilesSelectionRect {};

	QPixmap pixmap;
	QGraphicsScene *scene = nullptr;
	QGraphicsRectItem *cursorItem = nullptr;
};

