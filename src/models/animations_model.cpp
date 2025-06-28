#include "animations_model.hpp"

QVariant AnimationsModel::displayRoleData(int row, int column, Triple pointer) const
{
	const Animation *anim = accessor.value(row);
	if (!anim)
		return QVariant();

	if (column == 0) return anim->id;
	if (column == 1) return anim->name;

	return QVariant();
}

QVariant AnimationsModel::editRoleData(int row, int column, Triple pointer) const
{
	//
}

QVariant AnimationsModel::userRoleData(int row, int column, Triple pointer) const
{
	//
}

void AnimationsModel::setEditRoleData(int row, int column, const QVariant &value, Triple pointer)
{
	//
}

