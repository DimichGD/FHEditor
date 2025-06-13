#include "map_info_model.hpp"


MapInfo *MapInfoModel::mapInfo(int row)
{
	// TODO: check for valid id
	return accessor.element(row);
}

QVariant MapInfoModel::dataForDisplay(int row, int column) const
{
	const MapInfo *info = accessor.element(row);
	if (!info)
		return QVariant();

	if (column == 0) return info->id;
	if (column == 1) return info->name;

	return QVariant();
}

QVariant MapInfoModel::iconForDisplay(int row, int column) const
{
	return QVariant();
}

