#include "database.hpp"
//#include "iconset.hpp"
#include "json_stuff.hpp"
#include "settings.hpp"
//#include "rpgmmz/system_mz.hpp"

#include "items_model.hpp"

#include <QFile>
#include <QMessageBox>


Database *Database::Get()
{
	static Database db;
	return &db;
}

bool Database::load(Type type)
{
	if (Settings::Get()->lastPath.isEmpty())
		return false;

	QString path = Settings::Get()->lastPath;
	std::string buffer;
	QString errorMessage;

	// ------------ Items ------------
	if (type & Type::ITEMS)
	{
		getStorage<Item>().clear();
		QString filename = path + "/data/Items.json";
		if (!loadJson(filename, getStorage<Item>()))
			errorMessage += "Failed to load 'Items.json'\n";
	}

	// ----------- Weapons ------------
	if (type & Type::WEAPONS)
	{
		QString filename = path + "/data/Weapons.json";
		if (!loadJson(filename, getStorage<Weapon>()))
			errorMessage += "Failed to load 'Weapons.json'\n";
	}

	// ----------- Armors -------------
	if (type & Type::ARMORS)
	{
		QString filename = path + "/data/Armors.json";
		if (!loadJson(filename, getStorage<Armor>()))
			errorMessage += "Failed to load 'Armors.json'\n";
	}

	// ----------- Events ------------
	if (type & Type::EVENTS)
	{
		QString filename = path + "/data/CommonEvents.json";
		if (!loadJson(filename, getStorage<Event>()))
			errorMessage += "Failed to load 'CommonEvents.json'\n";
	}

	// ----------- System -----------
	if (type & Type::SYSTEM)
	{
		QString filename = path + "/data/System.json";
		if (!loadJson(filename, systemObject))
			errorMessage += "Failed to load 'System.json'\n";
		/*{
			errorMessage += "Failed to load 'System.json'\n";
			MZ::System systemMZObject;
			if (!loadJson(filename, systemMZObject))
			{
				errorMessage += "Failed to load 'System.json' as mz file\n";
			}
			else
			{
				currentVersion = Version::MZ;
			}
		}
		else
		{
			currentVersion = Version::MV;
		}*/
	}

	// ---------- Map Info -----------
	if (type & Type::MAP_INFO)
	{
		QString filename = path + "/data/MapInfos.json";
		if (!loadJson(filename, getStorage<MapInfo>()))
			errorMessage += "Failed to load 'MapInfos.json'\n";

		maps.clear();
	}

	// ---------- Tile Sets ----------
	if (type & Type::TILE_SETS)
	{
		QString filename = path + "/data/Tilesets.json";
		if (!loadJson(filename, getStorage<TileSet>()))
			errorMessage += "Failed to load 'Tilesets.json'\n";
	}

	// --------- Animations ----------
	if (type & Type::ANIMATION)
	{
		QString filename = path + "/data/Animations.json";
		if (!loadJson(filename, getStorage<Animation>()))
			errorMessage += "Failed to load 'Animations.json'\n";
	}

	// ----------- Skills ------------
	if (type & Type::SKILLS)
	{
		QString filename = path + "/data/Skills.json";
		if (!loadJson(filename, getStorage<Skill>()))
			errorMessage += "Failed to load 'Skills.json'\n";
	}

	// ----------- States ------------
	if (type & Type::STATES)
	{
		QString filename = path + "/data/States.json";
		if (!loadJson(filename, getStorage<State>()))
			errorMessage += "Failed to load 'States.json'\n";
	}

	// ----------- States ------------
	if (type & Type::ACTORS)
	{
		QString filename = path + "/data/Actors.json";
		if (!loadJson(filename, getStorage<Actor>()))
			errorMessage += "Failed to load 'Actors.json'\n";
	}

	// ----------- States ------------
	if (type & Type::CLASSES)
	{
		QString filename = path + "/data/Classes.json";
		if (!loadJson(filename, getStorage<Class>()))
			errorMessage += "Failed to load 'Classes.json'\n";
	}

	// -------- Error Message --------
	if (!errorMessage.isEmpty())
	{
		QMessageBox msgBox;
		msgBox.setText(errorMessage);
		msgBox.exec();
		return false;
	}

	//qDebug() << "loaded";
	return true;
}

bool Database::save(Type type)
{
	if (Settings::Get()->lastPath.isEmpty())
		return false;

	QString path = Settings::Get()->lastPath;

	// ------------ Items ------------
	if (type & Type::ITEMS)
	{
		QString filename = path + "/data/Items.json";
		if (!saveJson<Item>(filename, getStorage<Item>()))
			qDebug() << "Error while saving Items.json";
	}

	// ----------- Weapons ------------
	if (type & Type::WEAPONS)
	{
		QString filename = path + "/data/Weapons.json";
		if (!saveJson<Weapon>(filename, getStorage<Weapon>()))
			qDebug() << "Error while saving Weapons.json";
	}

	// ------------ Events ------------
	if (type & Type::EVENTS)
	{
		QString filename = path + "/data/CommonEvents.json";
		if (!saveJson<Event>(filename, getStorage<Event>()))
			qDebug() << "Error while saving CommonEvents.json";
	}

	// ------------- Maps ------------
	if (type & Type::MAP)
	{
		QString filename = path + "/data/MapInfos.json";
		if (!saveJson<MapInfo>(filename, getStorage<MapInfo>()))
			qDebug() << "Error while saving MapInfos.json";

		for (auto it: maps)
		{
			QString filename = QString("/data/Map%1.json").arg(it.first, 3, 10, QChar('0'));

			if (!saveJson<Map>(path + filename, it.second))
			{
				qDebug() << QString("Failed to save '%1'").arg(filename);
			}
		}
	}

	return true;
}

/*void Database::saveMap(int id)
{
	if (Settings::Get()->lastPath.isEmpty())
		return;

	auto it = maps.find(id);
	if (it == maps.end())
	{
		qDebug() << "Database::saveMap id" << id << "not found in cache";
		return;
	}

	//QString filename = Settings::Get()->lastPath + QString("/data/Map%1.json")
	//		.arg(id, 3, 10, QChar('0'));
	QString path = Settings::Get()->lastPath;
	QString filename = QString("Map%1.json").arg(id, 3, 10, QChar('0'));
	saveJson<Map>(path + "/data/" + filename, maps[id]);
}*/


Map *Database::map(int id)
{
	auto it = maps.find(id);
	if (it != maps.end())
		return &it->second;

	if (Settings::Get()->lastPath.isEmpty())
		return nullptr;

	QString path = Settings::Get()->lastPath;
	QString filename = QString("/data/Map%1.json").arg(id, 3, 10, QChar('0'));

	if (!loadJson(path + filename, maps[id]))
	{
		qDebug() << QString("Failed to load '%1'").arg(filename);
		maps.erase(id);
		return nullptr;
	}

	return &maps[id];
}



System *Database::system()
{
	return &systemObject;
}

QString Database::switchName(int id)
{
	if (id <= 0 || id >= std::ssize(systemObject.switches))
		return "?";

	return systemObject.switches[id];
}

QString Database::variableName(int id)
{
	if (id <= 0 || id >= std::ssize(systemObject.variables))
		return "?";

	return systemObject.variables[id];
}


/*template<typename T>
void forEach(std::vector<std::optional<T>> &vector, std::function<void(T&)> func)
{
	for (auto &entry: vector)
	{
		if (!entry.has_value())
			continue;

		T &item = entry.value();
		if (item.name.empty())
			continue;

		func(item);
	}
}*/
