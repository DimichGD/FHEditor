#pragma once
#include "map.hpp"
#include "tilemap.hpp"

#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsItem>

#include <map>


class EventGraphicsItem: public QGraphicsItem
{
public:
	EventGraphicsItem(MapEvent *event, QGraphicsItem *parent = nullptr);

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
	int eventId() const { return id; }

	static bool drawFullItem;

private:
	int id = 0;
	//MapEvent *event = nullptr;
};

// ------------------------------------------------------


class MapView: public QGraphicsView
{
	Q_OBJECT

public:
	enum Mode
	{
		TILES, EVENTS, PICKER,
	};

	MapView(QWidget *parent = nullptr);
	~MapView();

	void load(Map *map, TileMap *tileMap);
	void clear();

public slots:
	void setCurrentLayer(int layer) { currentLayer = layer; }
	void setCurrentMode(int mode);
	void setCurrentTileSingle(TileSet::Set setIndex, int x, int y);
	void setCurrentTileMultiple(TileSet::Set setIndex, const QRect &rect);
	void addNewEvent(MapEvent event);

signals:
	//void layerIsEmpty(int index);
	//void tileSelected(int x, int y, int tilesetIndex);
	void newEvent(int x, int y);
	void editEvent(int eventId);
	void pickTile(int tileId);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

	enum Operation
	{
		PAINT_SINGLE,
		PAINT_MULTIPLE,
	};

private:
	Operation currentOp = PAINT_SINGLE;
	Mode currentMode = TILES;

	bool isScrolling = false;
	QPoint scrollStart {};
	float scaleValue = 1.0f;

	bool isPainting = false;
	QPoint paintingStart {};
	QPoint lastTilePos {};

	int currentLayer = 0;
	TileItemInfo currentTileInfo {};
	QSize currentMultipleTileSize {};
	QList<TileItemInfo> currentMultipleTileInfoList {};

	QGraphicsRectItem *cursor = nullptr;

	int tileSize = 48;

	QGraphicsScene *scene = nullptr;
	TileMap *tileMap = nullptr;
	std::map<int, EventGraphicsItem *> eventItemMap;
};

