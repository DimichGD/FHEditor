#include "tilemap.hpp"
#include "database.hpp"
#include "images.hpp"

#include <stdexcept>

TileSet::Set tilesetIndexFromId(int id)
{
	/*switch (id & ~0xFF)
	{
		case 0:    return TileSet::B;
		case 256:  return TileSet::C;
		case 512:  return TileSet::D;
		case 768:  return TileSet::E;
		case 1536: return TileSet::A5;
		case 2048: return TileSet::A1;
		case 2816: return TileSet::A2;
		case 4352: return TileSet::A3;
		case 5888: return TileSet::A4;
	}*/

	if (id >= 0 && id < 256) return TileSet::B;
	else if (id >= 256 && id < 512) return TileSet::C;
	else if (id >= 512 && id < 768) return TileSet::D;
	else if (id >= 768 && id < 1536) return TileSet::E;
	else if (id >= 1536 && id < 2048) return TileSet::A5;
	else if (id >= 2048 && id < 2816) return TileSet::A1;
	else if (id >= 2816 && id < 4352) return TileSet::A2;
	else if (id >= 4352 && id < 5888) return TileSet::A3;
	else if (id >= 5888 && id < 8192) return TileSet::A4;

	qDebug() << "Unknown layer int id" << id;
	return TileSet::B;
}

int tileIdOffset(TileSet::Set index)
{
	switch (index)
	{
		case TileSet::B: return 0;
		case TileSet::C: return 256;
		case TileSet::D: return 512;
		case TileSet::E: return 768;
		case TileSet::A5: return 1536;
		case TileSet::A1: return 2048;
		case TileSet::A2: return 2816;
		case TileSet::A3: return 4352;
		case TileSet::A4: return 5888;
		case TileSet::COUNT: break;
	}

	qDebug() << "tileIdOffset" << index << "unreachable";
	return 0;
}

TileMap::TileMap()
{
	tileSets.resize(TileSet::COUNT);
	tileLayers.resize(6);
}

void TileMap::loadTileSet(int id)
{
	clear();

	TileSet *tileSet = Accessor<TileSet>().value(id);
	if (tileSet->tilesetNames.size() != TileSet::COUNT)
		throw std::runtime_error("tileSet->tilesetNames.size() != TileSet::Layer::COUNT");

	for (size_t i = 0; i < tileSet->tilesetNames.size(); i++)
	{
		QString &name = tileSet->tilesetNames[i];
		if (name.isEmpty())
			continue;

		QPixmap *pixmap = Images::Get()->tileSet(name);
		if (!pixmap)
			continue;

		tileSets[i] = pixmap;
		if (i >= TileSet::A1 && i < TileSet::A5)
			autoTilesFlag = true;

		mask.set(i);
	}
}

bool TileMap::loadTileMap(int id)
{
	map = Database::Get()->map(id);
	if (!map)
		return false;

	size_t arraySize = map->width * map->height;

	if (map->data.size() != arraySize * 6)
	{
		qDebug() << "map->data.size() != width * height * 6";
		return false;
	}

	for (size_t i = 0; i < 6; i++)
		tileLayers[i] = { map->data.begin() + arraySize * i, arraySize };

	loadTileSet(map->tilesetId); // make loadTileSet bool too
	model = new MapEventsModel(&map->events);
	return true;
}

int TileMap::tileId(int x, int y, int z)
{
	return tileLayers[z][y * map->width + x];
}

TileItemInfo TileMap::tileItemInfo(int tileId)
{
	TileSet::Set index = tilesetIndexFromId(tileId);
	tileId &= 0xFF;

	int x = tileId % 8;
	int y = tileId / 8;

	if (y >= 16) // FIXME: this will not work with A1..A4
	{
		x += 8;
		y -= 16;
	}

	return { tileSets[index], { x * tileSize, y * tileSize, tileSize, tileSize }, tileId };
}

TileItemInfo TileMap::tileItemInfo(int x, int y, TileSet::Set setIndex)
{
	int tileId = y * 8 + x + tileIdOffset(setIndex);

	if (y >= 16)
	{
		x += 8;
		y -= 16;
	}

	return { tileSets[setIndex], { x * tileSize, y * tileSize, tileSize, tileSize }, tileId };
}

void TileMap::putTile(int x, int y, int z, int id)
{
	tileLayers[z][y * width() + x] = id;
}

MapEvent *TileMap::addNewEvent(int x, int y)
{
	int lastEventId = 0;

	auto it = map->events.begin() + 1;
	while (it != map->events.end())
	{
		if (!it->has_value())
		{
			lastEventId = std::distance(it, map->events.begin());
			break;
		}

		std::advance(it, 1);
	}

	bool updateExisting = true;
	if (lastEventId == 0)
	{
		lastEventId = map->events.size();
		updateExisting = false;
	}


	/*MapEvent event { .id = lastEventId };
	event.name = QString("EV%1").arg(event.id, 3, 10, QChar('0'));
	event.x = x;
	event.y = y;
	event.pages.emplace_back();
	event.pages.back().list.push_back(Command::makeZeroCommand(0));*/

	if (updateExisting)
		map->events[lastEventId] = MapEvent::makeDefault(lastEventId, x, y);

	else
	{
		model->insertRows(model->rowCount(), 1);
		map->events.back() = MapEvent::makeDefault(lastEventId, x, y);
	}

	return &(*map->events.back());
}

void TileMap::clear()
{
	mask.reset();
	autoTilesFlag = false;

	for (int i = 0; i < TileSet::COUNT; i++)
		tileSets[i] = nullptr;
}


