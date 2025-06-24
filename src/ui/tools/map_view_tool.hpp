#pragma once
#include <QPoint>
#include <QObject>

class TileMap;
class QGraphicsScene;
class QGraphicsRectItem;

class MapViewTool: public QObject
{
	Q_OBJECT

public:
	MapViewTool(QGraphicsScene *scene, QGraphicsRectItem *cursor, QObject *parent)
		: QObject(parent)
	{
		this->scene = scene;
		this->cursor = cursor;
	}

	virtual ~MapViewTool() = default;
	virtual void activate() {}
	virtual void deactivate() {}
	virtual void mousePress(QPoint pos) { Q_UNUSED(pos) }
	virtual void mouseMove(QPoint pos) { Q_UNUSED(pos) }
	virtual void mouseRelease() {}
	virtual void mouseDoubleClick(QPoint pos) { Q_UNUSED(pos) }
	virtual void contextMenuRequested(QPoint pos) { Q_UNUSED(pos) }
	void setTileMap(TileMap *tileMap) { this->tileMap = tileMap; }

protected:
	TileMap *tileMap = nullptr;
	QGraphicsScene *scene = nullptr;
	QGraphicsRectItem *cursor = nullptr;
	int tileSize = 48;
};

