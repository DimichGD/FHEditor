#include "animations_model.hpp"

QVariant AnimationsModel::dataForDisplay(int row, int column) const
{
	const Animation *anim = accessor.value(row);
	if (!anim)
		return QVariant();

	if (column == 0) return anim->id;
	if (column == 1) return anim->name;

	return QVariant();
}
