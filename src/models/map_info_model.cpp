#include "map_info_model.hpp"


MapInfo *MapInfoModel::mapInfo(int row)
{
	// TODO: check for valid id
	return accessor.value(row);
}

QVariant MapInfoModel::displayRoleData(int row, int column, Triple pointer) const
{
	const MapInfo *info = accessor.value(row);
	if (!info)
		return QVariant();

	if (column == 0) return info->id;
	if (column == 1) return info->name;

	return QVariant();
}

QVariant MapInfoModel::editRoleData(int row, int column, Triple pointer) const
{

}

void MapInfoModel::setEditRoleData(int row, int column, const QVariant &value, Triple pointer)
{

}

