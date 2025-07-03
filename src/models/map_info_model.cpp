#include "map_info_model.hpp"
#include "database.hpp"

MapInfoModel::MapInfoModel(QObject *parent)
	: BaseModel2(&accessor, parent), accessor(Database::Get()->accessor<MapInfo>()) {}

MapInfo *MapInfoModel::mapInfo(int row)
{
	return accessor.value(row + 1);
}

QVariant MapInfoModel::data(int row, int column) const
{
	const MapInfo *mapInfo = accessor.value(row);
	if (!mapInfo) // map info can be null
		return QVariant();

	if (column == MapInfo::ID) return mapInfo->id;
	if (column == MapInfo::NAME) return mapInfo->name;

	return QVariant();
}

void MapInfoModel::setData(int row, int column, const QVariant &value)
{
	qDebug() << "MapInfoModel::setData";
}

