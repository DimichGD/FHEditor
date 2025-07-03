#pragma once
#include "map_view_tool.hpp"


class TilePickerTool: public MapViewTool
{
	Q_OBJECT

public:
	using MapViewTool::MapViewTool;

	void activate() override {}
	void deactivate() override {}
	void mousePress(QPoint pos) override;
	//void mouseMove(const QPoint &) override {}
	void mouseRelease() override {}
	//void mouseDoubleClick(const QPoint &) override {}

signals:
	void pickTile(int x, int y, int buttonIndex); // TODO: better naming

private:
	int buttonGroupIndex(int tileId);
	int lastLayer = 4;
	QPoint lastPos {};
};

