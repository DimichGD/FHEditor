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
	void mousePress(QPoint pos) override;
	void mouseMove(QPoint pos) override;
	void mouseRelease() override;
	void mouseDoubleClick(QPoint pos) override;

signals:
	void selectEvent(int eventId);

private:
	//QGraphicsRectItem *cursor = nullptr;
	int tileSize = 48;
};

