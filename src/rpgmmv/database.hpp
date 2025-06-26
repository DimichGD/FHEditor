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

#include <QString>
#include <QStandardItemModel>

#include <optional>
#include <map>

/*template<typename T>
concept hasIconIndex = requires(T t)
{
	t.iconIndex;
};*/

template<typename T>
struct Storage
{
	std::vector<std::optional<T>> data { std::nullopt };
};

class Database
{
public:
	//template<typename T>
	//using Storage = std::vector<std::optional<T>>;

	enum Type
	{
		ITEMS = 1,
		WEAPONS = 2,
		ARMORS = 4,
		EVENTS = 8,
		SYSTEM = 16,
		MAP_INFO = 32,
		TILE_SETS = 64,
		ANIMATION = 128,
		SKILLS = 256,
		STATES = 512,
		MAP = 1024,
		ACTORS = 2048,
		CLASSES = 4096,
		ENEMIES = 8192,
		TROOPS = 16384,
		ALL = ITEMS | WEAPONS | ARMORS | EVENTS | SYSTEM |
				MAP_INFO | TILE_SETS | ANIMATION | SKILLS | STATES |
				ACTORS | CLASSES | ENEMIES | TROOPS,
	};

	//Database(QObject *parent = nullptr): QObject(parent) {}

	static Database *Get();

	bool load(Type type);
	bool save(Type type);
	void saveMap(int id);

	//Item *item(int id);
	//Weapon *weapon(int id);
	//Armor *armor(int id);
	Event *event(int id);
	//MapInfo *mapInfo(int id);
	Map *map(int id);
	TileSet *tileSet(int id);
	Animation *animation(int id);
	Skill *skill(int id);
	State *state(int id);
	System *system();

	QString switchName(int id);
	QString variableName(int id);

	template<typename T>
	std::vector<std::optional<T>> &getStorage()
	{
		return std::get<Storage<T>>(storage).data;
	}

private:
	System systemObject;
	std::map<int, Map> maps;

	std::tuple<Storage<Item>, Storage<Weapon>, Storage<Armor>,
		Storage<Event>, Storage<MapInfo>, Storage<TileSet>,
		Storage<Animation>, Storage<Skill>, Storage<State>,
		Storage<Actor>, Storage<Class>, Storage<Enemy>, Storage<Troop>> storage;
};


class IAccessor
{
public:
	virtual ~IAccessor() = default;
	virtual int size() = 0;
	//virtual bool hasElement(int index) = 0;
	virtual void clearElement(int index) = 0;
	virtual void insertToEnd(int count) = 0;
	virtual void removeFromEnd(int count) = 0;
};


template<typename T>
class Accessor: public IAccessor
{
public:
	Accessor()
	{
		this->storage = &Database::Get()->getStorage<T>();
	}

	Accessor(std::vector<std::optional<T>> *storage)
	{
		this->storage = storage;
	}

	T *value(int id)
	{
		return const_cast<T *>(std::as_const(*this).value(id));
	}

	const T *value(int id) const
	{
		if (id < 0 || id >= std::ssize(*storage))
			return nullptr;

		if (!storage->at(id).has_value())
			return nullptr;

		return &storage->at(id).value();
	}

	int size() override
	{
		return storage->size();
	}

	/*bool hasElement(int index) override
	{
		return value(index) != nullptr;
	}*/

	void clearElement(int index) override
	{
		int prevId = value(index)->id;
		*value(index) = { .id = prevId };
	}

	void insertToEnd(int count) override
	{
		int nextId = storage->back().value().id + 1;
		for (int i = 0; i < count; i++)
			storage->emplace_back( T { .id = nextId++ } );
	}

	void removeFromEnd(int count) override
	{
		storage->erase(storage->end() - count, storage->end());
	}

private:
	std::vector<std::optional<T>> *storage;
};
