#pragma once
#include "actor.hpp"
#include "class.hpp"
#include "enemy.hpp"
#include "item.hpp"
#include "event.hpp"
#include "map.hpp"
#include "map_info.hpp"
#include "skill.hpp"
#include "tileset.hpp"
#include "troop.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "animation.hpp"
#include "system.hpp"
#include "state.hpp"
#include "accessor.hpp"

//#include <QString>
//#include <QStandardItemModel>

//#include <optional>
#include <map>


template<typename T>
using Storage = std::vector<std::optional<T>>;

/*using Tuple = std::tuple<
	Storage<Item>, Storage<Weapon>, Storage<Armor>,
	Storage<Event>, Storage<MapInfo>, Storage<TileSet>,
	Storage<Animation>, Storage<Skill>, Storage<State>,
	Storage<Actor>, Storage<Class>, Storage<Enemy>, Storage<Troop>
>;*/



class Database
{
public:
	enum Type
	{
		ITEMS     = 1 << 0,
		WEAPONS   = 1 << 2,
		ARMORS    = 1 << 3,
		EVENTS    = 1 << 4,
		SYSTEM    = 1 << 5,
		MAP_INFO  = 1 << 6,
		TILE_SETS = 1 << 7,
		ANIMATION = 1 << 8,
		SKILLS    = 1 << 9,
		STATES    = 1 << 10,
		MAP       = 1 << 11,
		ACTORS    = 1 << 12,
		CLASSES   = 1 << 13,
		ENEMIES   = 1 << 14,
		TROOPS    = 1 << 15,
		ALL = ITEMS | WEAPONS | ARMORS | EVENTS | SYSTEM |
				MAP_INFO | TILE_SETS | ANIMATION | SKILLS | STATES |
				ACTORS | CLASSES | ENEMIES | TROOPS,
	};

	//Database();
	//~Database();

	static Database *Get();

	bool load(Type type);
	bool save(Type type);
	//void saveMap(int id);

	Map *map(int id);
	System *system();

	QString switchName(int id);
	QString variableName(int id);

	template<typename T>
	Accessor<T> accessor()
	{
		return Accessor<T>(&getStorage<T>());
	}

	template<typename T>
	Storage<T> &getStorage()
	{
		return std::get<Storage<T>>(storage);
	}

private:
	System systemObject;
	std::map<int, Map> maps;

	std::tuple<Storage<Item>, Storage<Weapon>, Storage<Armor>,
		Storage<Event>, Storage<MapInfo>, Storage<TileSet>,
		Storage<Animation>, Storage<Skill>, Storage<State>,
		Storage<Actor>, Storage<Class>, Storage<Enemy>, Storage<Troop>> storage;
};
