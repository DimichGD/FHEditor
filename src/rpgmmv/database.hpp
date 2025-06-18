#pragma once
#include "item.hpp"
#include "event.hpp"
#include "map.hpp"
#include "map_info.hpp"
#include "skill.hpp"
#include "tileset.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "animation.hpp"
#include "system.hpp"
#include "state.hpp"

#include <QString>
#include <QStandardItemModel>

#include <optional>
#include <map>

template<typename T>
concept hasIconIndex = requires(T t)
{
	t.iconIndex;
};

template<typename ValueType>
struct Storage
{
	std::vector<std::optional<ValueType>> vector;

	ValueType *value(int id)
	{
		if (id < 0 || id >= std::ssize(vector))
			return nullptr;

		if (!vector[id].has_value())
			return nullptr;

		return &vector[id].value();
	}

	const ValueType *value(int id) const
	{
		if (id < 0 || id >= std::ssize(vector))
			return nullptr;

		if (!vector[id].has_value())
			return nullptr;

		return &vector[id].value();
	}
};


class Database
{
public:
	enum Version
	{
		MV, MZ,
	};

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
		STATE = 512,
		MAP = 1024,
		ALL = ITEMS | WEAPONS | ARMORS | EVENTS | SYSTEM |
				MAP_INFO | TILE_SETS | ANIMATION | SKILLS | STATE,
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
	MapInfo *mapInfo(int id);
	Map *map(int id);
	TileSet *tileSet(int id);
	Animation *animation(int id);
	Skill *skill(int id);
	State *state(int id);
	System *system();

	template<typename ValueType>
	ValueType *value(int id)
	{
		auto &vector = getVector<ValueType>();

		if constexpr (std::is_same<ValueType, Animation>::value)
		{
			id += 1;
		}

		if (id < 0 || id >= std::ssize(vector))
			return nullptr;

		if (!vector[id].has_value())
			return nullptr;

		return &vector[id].value();
	}

	template<typename ValueType,
			 typename VectorType = std::vector<std::optional<ValueType>>>
	VectorType &getVector()
	{
		return std::get<Storage<ValueType>>(storage).vector;
	}

	template<typename ValueType>
	Storage<ValueType> &getStorage()
	{
		return std::get<Storage<ValueType>>(storage);
	}

private:
	System systemObject;
	Map mapObject;

	std::tuple<Storage<Item>, Storage<Weapon>, Storage<Armor>,
		Storage<Event>, Storage<MapInfo>, Storage<TileSet>,
		Storage<Animation>, Storage<Skill>, Storage<State>> storage;
};


class IAccessor
{
public:
	virtual ~IAccessor() = default;
	//virtual void load() = 0;
	virtual int  size() = 0;
	//virtual void element(int index) = 0;
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

	int size() override
	{
		return storage->vector.size();
	}

	T *element(int index)
	{
		return storage->value(index);
	}

	const T *element(int index) const
	{
		return storage->value(index);
	}

	void clearElement(int index) override
	{
		int prevId = storage->value(index)->id;
		*storage->value(index) = { .id = prevId };
	}

	void insertToEnd(int count) override
	{
		int nextId = storage->vector.back().value().id + 1;
		for (int i = 0; i < count; i++)
			storage->vector.push_back({{ .id = nextId++ }});
	}

	void removeFromEnd(int count) override
	{
		storage->vector.erase(storage->vector.end() - count, storage->vector.end());
	}

private:
	Storage<T> *storage;
};
