#include "map_view_tool.hpp"

MapViewTool::MapViewTool(TileMap *tileMap, QGraphicsScene *scene, QGraphicsRectItem *cursor, QObject *parent)
	: QObject(parent)
{
	this->tileMap = tileMap;
	this->scene = scene;
	this->cursor = cursor;
}
