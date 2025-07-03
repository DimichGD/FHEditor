#pragma once
#include "map.hpp"
#include "map_events_model.hpp"
#include "tileset.hpp"
#include <QPixmap>
#include <bitset>
#include <span>

struct TileItemInfo
{
	QPixmap *pixmap = nullptr;
	QRect rect {};
	int id = -1;
};

int tileIdOffset(TileSet::Set index);
TileSet::Set tilesetIndexFromId(int id);
QString makeMapName(int id);

class TileMap
{
public:
	TileMap();

	bool loadTileMap(int id);

	bool hasAutoTiles() const { return autoTilesFlag; }
	bool hasTileSet(TileSet::Set setIndex) { return mask[setIndex]; }

	QPixmap *pixmap(int index) { return tileSets[index]; }
	int tileId(int x, int y, int z);
	TileItemInfo tileItemInfo(int tileId);
	TileItemInfo tileItemInfo(int x, int y, TileSet::Set setIndex);

	void putTile(int x, int y, int z, int id);
	//MapEvent *addNewEvent(int x, int y);

	int width() { return map->width; }
	int height() { return map->height; }
	void clear();

	//std::vector<std::optional<MapEvent>> *events() { return &map->events; }
	void setEventsModel(MapEventsModel *model);

protected:
	//void generatePixmapForSet(int index);
	void loadTileSet(int id);

private:
	bool autoTilesFlag = false;
	Map *map = nullptr; // FIXME: load once here or in map_tab.cpp
	int tileSize = 48;
	std::bitset<TileSet::COUNT> mask;
	QList<std::span<int>> tileLayers;
	QList<QPixmap *> tileSets;

	//MapEventsModel *model = nullptr;
};

