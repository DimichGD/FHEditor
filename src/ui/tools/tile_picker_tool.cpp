#include "tile_picker_tool.hpp"
#include "tilemap.hpp"

void TilePickerTool::mousePress(QPoint pos)
{
	if (pos == lastPos)
	{
		--lastLayer;

		if (lastLayer < 0)
			lastLayer = 4;
	}
	else
	{
		lastLayer = 4;
		lastPos = pos;
	}

	for (int i = lastLayer; i >= 0; i--)
	{
		int tileId = tileMap->tileId(pos.x(), pos.y(), i);
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
