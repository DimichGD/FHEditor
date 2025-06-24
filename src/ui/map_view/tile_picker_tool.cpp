#include "tile_picker_tool.hpp"

/*TilePickerTool::TilePickerTool(QGraphicsScene *scene, QObject *parent)
	: MapViewTool(parent)
{
	this->scene = scene; // TODO: get cursor to every tool, maybe make factory in map_view.cpp
}*/

void TilePickerTool::mousePress(int x, int y)
{
	if (QPoint(x, y) == lastPos)
	{
		--lastLayer;

		if (lastLayer < 0)
			lastLayer = 4;
	}
	else
	{
		lastLayer = 4;
		lastPos = QPoint(x, y);
	}

	for (int i = lastLayer; i >= 0; i--)
	{
		int tileId = tileMap->tileId(x, y, i);
		if (tileId == 0)
			continue;

		emit pickTile(tileId, buttonGroupIndex(tileId));
		lastLayer = i;
		break;
	}
}

int TilePickerTool::buttonGroupIndex(int tileId)
{
	TileSet::Set setIndex = tilesetIndexFromId(tileId);
	if (setIndex >= TileSet::A1 && setIndex <= TileSet::A4)
	{
		qDebug() << "MapView::pickTile autotile is not supported";
		return 0;
	}

	else if (setIndex == TileSet::A5)
		return 0;

	else
		return setIndex - 4;
}
