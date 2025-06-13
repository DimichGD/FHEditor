#pragma once
#include "map.hpp"
#include "tilemap.hpp"

#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsItem>

#include <map>
#include <vector>
#include <array>

// ------------------------------------------------------

class EventGraphicsItem: public QGraphicsItem
{
public:
	EventGraphicsItem(int eventId, QGraphicsItem *parent = nullptr);

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
	int eventId() const { return id; }

	static bool drawFullItem;

private:
	int id = -1;
};

// ------------------------------------------------------

/*class TileGraphicsItem: public QGraphicsItem
{
public:
	TileGraphicsItem(int tileSize, QGraphicsItem *parent = nullptr);

	void setInfo(size_t layer, TileGraphicsInfo info);
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
	QRect rect;
	std::array<TileGraphicsInfo, 6> infos {};
};*/

// ------------------------------------------------------

/*struct GraphicsItemGroup
{
	std::vector<TileGraphicsItem *> items;
};*/

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
	void layersToggled(int id, bool toggled);
	void setCurrentLayer(int layer) { currentLayer = layer; }
	void setCurrentMode(int mode);
	void setCurrentTileSingle(TileSet::Set setIndex, int x, int y);
	void setCurrentTileMultiple(TileSet::Set setIndex, const QRect &rect);

signals:
	void layerIsEmpty(int index);
	void tileSelected(int x, int y, int tilesetIndex);
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
		//NONE,
		PAINT_SINGLE,
		PAINT_MULTIPLE,
		//PAINT_RECT,
		//SCROLL,
	};

	/*enum class Tool
	{
		PAINT_SINGLE,
		PAINT_MULTIPLE,
		PAINT_RECT,
		EVENT,
	};*/


//private:
public:
	//Operation prevOp = NONE;
	Operation currentOp = PAINT_SINGLE;
	Mode currentMode = TILES;
	//Operation currentOp = Operation::NONE;
	//Tool currentTool = Tool::PAINT_SINGLE;

	bool isScrolling = false;
	QPoint scrollStart {};
	float scaleValue = 1.0f;

	bool isPainting = false;
	QPoint paintingStart {};
	QPoint lastTilePos {};

	//bool multiTileMode = false;
	//QRect multiTileRect {};
	//QList<int> multiTileTiles {};
	int currentLayer = 0;
	TileGraphicsInfo currentTileInfo {};
	QSize currentMultipleTileSize {};
	QList<TileGraphicsInfo> currentMultipleTileInfoList {};

	QGraphicsRectItem *cursor = nullptr;

	//int currentLoadingLayer = 0;
	int tileSize = 48;
	//int drawTileId = -1;

	//Map *currentMap = nullptr;
	QGraphicsScene *scene = nullptr;
	//std::vector<QPixmap *> tilesets;
	//std::map<std::string, QPixmap> tilesetsCache;
	TileMap *tileMap = nullptr;
	std::map<int, EventGraphicsItem *> eventItemMap;
	//std::array<GraphicsItemGroup, 6> groups;
	//std::vector<TileGraphicsItem *> tiles;
};

