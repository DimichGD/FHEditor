#include "database.hpp"
//#include "iconset.hpp"
#include "json_stuff.hpp"
#include "settings.hpp"
//#include "rpgmmz/system_mz.hpp"

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
		QString filename = path + "/data/Items.json";
		if (!loadJson(filename, getVector<Item>()))
			errorMessage += "Failed to load 'Items.json'\n";
	}

	// ----------- Weapons ------------
	if (type & Type::WEAPONS)
	{
		QString filename = path + "/data/Weapons.json";
		if (!loadJson(filename, getVector<Weapon>()))
			errorMessage += "Failed to load 'Weapons.json'\n";
	}

	// ----------- Armors -------------
	if (type & Type::ARMORS)
	{
		QString filename = path + "/data/Armors.json";
		if (!loadJson(filename, getVector<Armor>()))
			errorMessage += "Failed to load 'Armors.json'\n";
	}

	// ----------- Events ------------
	if (type & Type::EVENTS)
	{
		QString filename = path + "/data/CommonEvents.json";
		if (!loadJson(filename, getVector<Event>()))
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
		if (!loadJson(filename, getVector<MapInfo>()))
			errorMessage += "Failed to load 'MapInfos.json'\n";
	}

	// ---------- Tile Sets ----------
	if (type & Type::TILE_SETS)
	{
		QString filename = path + "/data/Tilesets.json";
		if (!loadJson(filename, getVector<TileSet>()))
			errorMessage += "Failed to load 'Tilesets.json'\n";
	}

	// --------- Animations ----------
	if (type & Type::ANIMATION)
	{
		QString filename = path + "/data/Animations.json";
		if (!loadJson(filename, getVector<Animation>()))
			errorMessage += "Failed to load 'Animations.json'\n";
	}

	// ----------- Skills ------------
	if (type & Type::SKILLS)
	{
		QString filename = path + "/data/Skills.json";
		if (!loadJson(filename, getVector<Skill>()))
			errorMessage += "Failed to load 'Skills.json'\n";
	}

	// ----------- States ------------
	if (type & Type::STATE)
	{
		QString filename = path + "/data/States.json";
		if (!loadJson(filename, getVector<State>()))
			errorMessage += "Failed to load 'States.json'\n";
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
		if (!saveJson<Item>(filename, getVector<Item>()))
			qDebug() << "Error while saving Items.json";
	}

	// ----------- Weapons ------------
	if (type & Type::WEAPONS)
	{
		QString filename = path + "/data/Weapons.json";
		if (!saveJson<Weapon>(filename, getVector<Weapon>()))
			qDebug() << "Error while saving Weapons.json";
	}

	// ------------ Events ------------
	if (type & Type::EVENTS)
	{
		QString filename = path + "/data/CommonEvents.json";
		if (!saveJson<Event>(filename, getVector<Event>()))
			qDebug() << "Error while saving CommonEvents.json";
	}

	return true;
}

void Database::saveMap(int id)
{
	if (Settings::Get()->lastPath.isEmpty())
		return;

	QString path = Settings::Get()->lastPath;
	QString filename = path + QString("/data/Map%1.json")
			.arg(id, 3, 10, QChar('0'));
	saveJson<Map>(filename, mapObject);
}

template<typename T>
T *vectorValue(std::vector<std::optional<T>> &vector, int id)
{
	if (id < 0 || id >= std::ssize(vector))
		return nullptr;

	if (!vector[id].has_value())
		return nullptr;

	return &vector[id].value();
}

/*Item *Database::item(int id)
{
	return vectorValue(getVector<Item>(), id);
}

Weapon *Database::weapon(int id)
{
	return vectorValue(getVector<Weapon>(), id);
}

Armor *Database::armor(int id)
{
	return vectorValue(getVector<Armor>(), id);
}*/

Event *Database::event(int id)
{
	return vectorValue(getVector<Event>(), id);
}

MapInfo *Database::mapInfo(int id)
{
	return vectorValue(getVector<MapInfo>(), id);
}

Map *Database::map(int id)
{
	/*auto it = maps.find(id);
	if (it != maps.end())
		return &it->second;*/

	if (Settings::Get()->lastPath.isEmpty())
		return nullptr;

	QString path = Settings::Get()->lastPath;
	QString filename = QString("Map%1.json").arg(id, 3, 10, QChar('0'));

	//maps[id] = {};
	if (!loadJson(path + "/data/" + filename, mapObject))
	{
		qDebug() << QString("Failed to load '%1'").arg(filename);
		//maps.erase(id);
		return nullptr;
	}

	return &mapObject;
}

TileSet *Database::tileSet(int id)
{
	return vectorValue(getVector<TileSet>(), id);
}

Animation *Database::animation(int id)
{
	return vectorValue(getVector<Animation>(), id);
}

Skill *Database::skill(int id)
{
	return vectorValue(getVector<Skill>(), id);
}

State *Database::state(int id)
{
	return vectorValue(getVector<State>(), id);
}

System *Database::system()
{
	return &systemObject;
}

template<typename T>
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
}

/*QStandardItemModel *Database::createItemsModel()
{
	itemsModel = createModel({ "ID", "Icon", "Name" });
	forEach<Item>(items, [this](Item &item)
	{
		addRow(itemsModel, item.id, item.name, item.iconIndex);
	});

	return itemsModel;
}*/

/*QStandardItemModel *Database::createWeaponsModel()
{
	weaponsModel = createModel({ "ID", "Icon", "Name" });
	forEach<Weapon>(weapons, [this](Weapon &weapon)
	{
		addRow(weaponsModel, weapon.id, weapon.name, weapon.iconIndex);
	});

	return weaponsModel;
}*/

/*QStandardItemModel *Database::createEventsModel()
{
	eventsModel = createModel({ "ID", "Name" });
	for (auto &entry: events)
	{
		if (!entry.has_value())
			continue;

		Event &event = entry.value();
		addRow(eventsModel, event.id, event.name);
	}

	return eventsModel;
}*/

/*QStandardItemModel *Database::createMapInfoModel()
{
	mapInfoModel = createModel({ "ID", "Name" });
	forEach<MapInfo>(mapInfos, [this](MapInfo &mapInfo)
	{
		addRow(mapInfoModel, mapInfo.id, mapInfo.name, -1);
	});

	return mapInfoModel;
}

QStandardItemModel *Database::createModel(QStringList columns)
{
	QStandardItemModel *model = new QStandardItemModel();
	model->setColumnCount(columns.size());
	for (int i = 0; i < columns.size(); i++)
		model->setHeaderData(i, Qt::Horizontal, columns[i]);

	return model;
}*/

/*QStandardItemModel *Database::createModel(int columnCount)
{
	QStandardItemModel *model = new QStandardItemModel();
	model->setColumnCount(columnCount);
	model->setHeaderData(0, Qt::Horizontal, "ID");
	if (columnCount == 3)
	{
		model->setHeaderData(1, Qt::Horizontal, "Icon");
		model->setHeaderData(2, Qt::Horizontal, "Name");
	}
	else if (columnCount == 2)
		model->setHeaderData(1, Qt::Horizontal, "Name");

	return model;
}*/

/*void Database::addRow(QStandardItemModel *model, int id, std::string name)
{
	QStandardItem *idItem = new QStandardItem();
	idItem->setData(id, Qt::DisplayRole);

	QStandardItem *nameItem = new QStandardItem();
	nameItem->setData(QString::fromStdString(name), Qt::DisplayRole);

	QList<QStandardItem *> item_row { idItem, nameItem };
	model->appendRow(item_row);
}*/

/*void Database::addRow(QStandardItemModel *model, int id, std::string name, int iconIndex)
{
	QStandardItem *idItem = new QStandardItem();
	idItem->setData(id, Qt::DisplayRole);

	QStandardItem *nameItem = new QStandardItem();
	nameItem->setData(QString::fromStdString(name), Qt::DisplayRole);

	if (iconIndex == -1)
	{
		model->appendRow({ idItem, nameItem });
	}
	else
	{
		QStandardItem *imageItem = new QStandardItem();
		imageItem->setData(IconSet::Get()->get(iconIndex), Qt::DecorationRole);

		model->appendRow({ idItem, imageItem, nameItem });
	}
}

void Database::removeRow(QStandardItemModel *model, int index)
{
	Q_UNUSED(model)
	Q_UNUSED(index)
	qDebug() << "Database::removeRow";
}*/
