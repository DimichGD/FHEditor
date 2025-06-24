#pragma once
#include "tilemap.hpp"
#include <QGraphicsScene>
#include <QObject>

class MapViewTool: public QObject
{
	Q_OBJECT

public:
	//MapViewTool(QObject *parent = nullptr): QObject(parent) {}
	MapViewTool(TileMap *tileMap, QGraphicsScene *scene, QGraphicsRectItem *cursor, QObject *parent);

	virtual ~MapViewTool() = default;
	virtual void activate() = 0;
	virtual void deactivate() = 0;
	virtual void mousePress(int x, int y) = 0;
	virtual void mouseMove(int x, int y) = 0;
	virtual void mouseRelease() = 0;
	virtual void mouseDoubleClick(int x, int y) = 0;

	void setTileMap(TileMap *tileMap) { this->tileMap = tileMap; }
	void setScene(QGraphicsScene *scene) { this->scene = scene; }
	void setCursor(QGraphicsRectItem *cursor) { this->cursor = cursor; }

protected:
	friend class MapView;
	TileMap *tileMap = nullptr;
	QGraphicsScene *scene = nullptr;
	QGraphicsRectItem *cursor = nullptr;
	int tileSize = 48;
};

