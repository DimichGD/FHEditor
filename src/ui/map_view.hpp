#pragma once
#include "map.hpp"
#include "map_view_tool.hpp"
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
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
	int eventId() const { return event->id; }
	void updatePixmap(QRect bounds, QPixmap *pixmap, QRect rect)
	{
		prepareGeometryChange();
		this->bounds = bounds;
		this->pixmap = pixmap;
		this->pixmapRect = rect;
		update();
	}

	static bool drawFullItem;

private:
	QRect bounds { 0, 0, 48, 48 };
	QPixmap *pixmap = nullptr;
	QRect pixmapRect {};
	MapEvent *event = nullptr;
};


// ------------------------------------------------------

class MapView: public QGraphicsView
{
	Q_OBJECT

public:
	/*enum Mode
	{
		TILES, EVENTS, PICKER,
	};*/

	MapView(QWidget *parent = nullptr);
	~MapView();

	QGraphicsScene *currentScene() { return scene; }
	void load(TileMap *tileMap);
	void clear();

	template<typename T>
	T *makeTool() { return new T(scene, cursor, this); }

public slots:
	void setCurrentTool(MapViewTool *tool) { currentTool = tool; }
	//void setCurrentLayer(int layer) { currentLayer = layer; }
	void setCurrentMode(int mode);
	//void addNewEvent(MapEvent event);

signals:
	//void layerIsEmpty(int index);
	//void tileSelected(int x, int y, int tilesetIndex);
	//void newEvent(int x, int y);
	//void editEvent(int eventId);
	//void pickTile(int tileId);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void drawForeground(QPainter *painter, const QRectF &rect) override;
	void wheelEvent(QWheelEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
	void startAsyncLoad();
	void completeAsyncLoad();

private:
	MapViewTool *currentTool = nullptr;

	bool isScrolling = false;
	QPoint scrollStart {};
	QPoint lastTilePos {};
	float scaleValue = 1.0f;
	int tileSize = 48;

	QGraphicsRectItem *cursor = nullptr;
	QGraphicsScene *scene = nullptr;
	TileMap *tileMap = nullptr;
	std::map<int, EventGraphicsItem *> eventItemMap;
};

