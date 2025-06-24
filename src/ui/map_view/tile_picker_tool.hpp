#pragma once
#include "map_view_tool.hpp"


class TilePickerTool: public MapViewTool
{
	Q_OBJECT

public:
	//TilePickerTool(QGraphicsScene *scene, QObject *parent = nullptr);
	using MapViewTool::MapViewTool;

	void activate() override {}
	void deactivate() override {}
	void mousePress(int x, int y) override;
	void mouseMove(int, int) override {}
	void mouseRelease() override {}
	void mouseDoubleClick(int, int) override {}

signals:
	void pickTile(int tileId, int buttonIndex);

private:
	int buttonGroupIndex(int tileId);
	int lastLayer = 4;
	QPoint lastPos {};
};

