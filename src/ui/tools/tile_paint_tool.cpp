#include "tile_paint_tool.hpp"
#include <QGraphicsRectItem>
#include <QGraphicsScene>

void TilePaintTool::mousePress(QPoint pos)
{
	if (currentMultipleTileInfoList.empty())
		return;

	if (currentMultipleTileSize.width() * currentMultipleTileSize.height() == 1)
	{
		tileMap->putTile(pos.x(), pos.y(), currentLayer, currentMultipleTileInfoList[0].id);
		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize, tileSize, tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
	}
	else
	{
		int index = 0;
		for (int y = pos.y(); y < pos.y() + currentMultipleTileSize.height(); y++)
		{
			for (int x = pos.x(); x < pos.x() + currentMultipleTileSize.width(); x++)
			{
				tileMap->putTile(x, y, currentLayer, currentMultipleTileInfoList[index].id);
				// FIXME: clamp x and y by map size
				++index;
			}
		}

		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize,
			currentMultipleTileSize.width() * tileSize,
			currentMultipleTileSize.height() * tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
	}

	isPainting = true;
	paintingStart = pos;
}

void TilePaintTool::mouseMove(QPoint pos)
{
	pos.rx() = std::min(tileMap->width() - 1, std::max(0, pos.x()));
	pos.ry() = std::min(tileMap->height() - 1, std::max(0, pos.y()));

	cursor->setPos(pos.x() * tileSize, pos.y() * tileSize);
	cursor->update();

	/*if (isPainting && currentOp == PAINT_SINGLE)
	{
		tileMap->putTile(pos.x(), pos.y(), currentLayer, currentTileInfo.id);
		QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize, tileSize, tileSize);
		scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
	}*/

	if (isPainting)
	{
		if (currentMultipleTileSize.width() * currentMultipleTileSize.height() == 1)
		{
			tileMap->putTile(pos.x(), pos.y(), currentLayer, currentMultipleTileInfoList[0].id);
			QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize, tileSize, tileSize);
			scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
		}
		else
		{
			int w = currentMultipleTileSize.width();
			int h = currentMultipleTileSize.height();
			for (int y = pos.y(); y < pos.y() + h; y++)
			{
				for (int x = pos.x(); x < pos.x() + w; x++)
				{
					int index = (std::abs(y - paintingStart.y()) % h) * w
							+ (std::abs(x - paintingStart.x()) % w);
					tileMap->putTile(x, y, currentLayer, currentMultipleTileInfoList[index].id);
					// FIXME: handle zero tile in any set
					++index;
				}
			}

			QRect invalidateRect = QRect(pos.x() * tileSize, pos.y() * tileSize,
				currentMultipleTileSize.width() * tileSize,
				currentMultipleTileSize.height() * tileSize);
			scene->invalidate(invalidateRect, QGraphicsScene::BackgroundLayer);
		}
	}
}

void TilePaintTool::mouseRelease()
{
	isPainting = false;
}

/*void TilePaintTool::setCurrentTileSingle(TileSet::Set setIndex, int x, int y)
{
	QRect rect(x, y, 1, 1);

	QList<TileItemInfo> tileInfos;
	tileInfos.reserve(rect.width() * rect.height());

	for (int y = rect.top(); y <= rect.bottom(); y++)
		for (int x = rect.left(); x <= rect.right(); x++)
			tileInfos.append(tileMap->tileItemInfo(x, y, setIndex));

	currentMultipleTileSize = rect.size();
	currentMultipleTileInfoList = tileInfos;

	cursor->setRect(2, 2, rect.size().width() * tileSize - 3, rect.size().height() * tileSize - 3);
}*/

void TilePaintTool::setCurrentTileMultiple(TileSet::Set setIndex, const QRect &rect)
{
	QList<TileItemInfo> tileInfos;
	tileInfos.reserve(rect.width() * rect.height());

	for (int y = rect.top(); y <= rect.bottom(); y++)
		for (int x = rect.left(); x <= rect.right(); x++)
			tileInfos.append(tileMap->tileItemInfo(x, y, setIndex));

	currentMultipleTileSize = rect.size();
	currentMultipleTileInfoList = tileInfos;

	//cursor->setRect(0, 0, rect.size().width() * tileSize, rect.size().height() * tileSize);
	cursor->setRect(2, 2, rect.size().width() * tileSize - 3, rect.size().height() * tileSize - 3);
}
