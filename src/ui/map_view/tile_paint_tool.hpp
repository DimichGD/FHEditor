#pragma once

#include "map_view_tool.hpp"

class TilePaintTool : public MapViewTool
{
	Q_OBJECT

public:
	//TilePaintTool(QGraphicsScene *scene, QGraphicsRectItem *cursor, QObject *parent = nullptr);
	//TilePaintTool(QObject *parent = nullptr): MapViewTool(parent) {}
	using MapViewTool::MapViewTool;

	void activate() override {}
	void deactivate() override {}
	void mousePress(int x, int y) override;
	void mouseMove(int, int) override;
	void mouseRelease() override;
	void mouseDoubleClick(int, int) override {}

	void setCurrentLayer(int layer) { currentLayer = layer; }
	void setCurrentTileSingle(TileSet::Set setIndex, int x, int y);
	void setCurrentTileMultiple(TileSet::Set setIndex, const QRect &rect);

private:
	int currentLayer = 0;
	TileItemInfo currentTileInfo {};
	QSize currentMultipleTileSize {};
	QList<TileItemInfo> currentMultipleTileInfoList {};

	bool isPainting = false;
	QPoint paintingStart {};
};

