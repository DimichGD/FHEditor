#pragma once
#include "map_view_tool.hpp"

class MapEventTool: public MapViewTool
{
	Q_OBJECT

public:
	//MapEventTool(QGraphicsScene *scene, QObject *parent = nullptr);
	using MapViewTool::MapViewTool;

	void activate() override {}
	void deactivate() override {}
	void mousePress(int x, int y) override;
	void mouseMove(int x, int y) override;
	void mouseRelease() override;
	void mouseDoubleClick(int x, int y) override;

signals:
	void selectEvent(int eventId);

private:
	//QGraphicsRectItem *cursor = nullptr;
	int tileSize = 48;
};

