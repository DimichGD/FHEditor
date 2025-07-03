#include "animations_model.hpp"
#include "database.hpp"

AnimationsModel::AnimationsModel(QObject *parent)
	: BaseModel2(&accessor, parent), accessor(Database::Get()->accessor<Animation>()) {}

Animation *AnimationsModel::animation(int row)
{
	return accessor.value(row + 1);
}

QVariant AnimationsModel::data(int id, int column) const
{
	const Animation *anim = accessor.value(id);

	if (column == Animation::ID) return anim->id;
	if (column == Animation::NAME) return anim->name;

	return QVariant();
}

void AnimationsModel::setData(int id, int column, const QVariant &value)
{
	qDebug() << "AnimationsModel::setData";
}

