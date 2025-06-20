#pragma once
#include "map.hpp"
#include "tileset.hpp"
#include <QPixmap>
#include <bitset>
#include <span>

struct TileItemInfo
{
	QRect rect = QRect();
	QPixmap *pixmap = nullptr;
	int id = -1;
	//TileSet::Set tileSet = TileSet::A5;
};

int tileIdOffset(TileSet::Set index);
TileSet::Set tilesetIndexFromId(int id);

class TileMap
{
public:
	TileMap();

	void loadTileMap(int id);

	bool hasAutoTiles() const { return autoTilesFlag; }
	bool hasTileSet(int index) { return mask[index]; }

	QPixmap *pixmap(int index) { return tileSets[index]; }
	int tileId(int x, int y, int z);
	TileItemInfo tileItemInfo(int tileId);
	TileItemInfo tileItemInfo(int x, int y, TileSet::Set setIndex);

	void putTile(int x, int y, int z, int id);

	int width() { return map->width; }
	int height() { return map->height; }
	void clear();

protected:
	//void generatePixmapForSet(int index);
	void loadTileSet(int id);

private:
	bool autoTilesFlag = false;
	Map *map = nullptr;
	int tileSize = 48;
	std::bitset<TileSet::COUNT> mask;
	QList<std::span<int>> tileLayers;
	QList<QPixmap *> tileSets;
};

