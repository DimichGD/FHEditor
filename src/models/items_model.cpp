#include "items_model.hpp"


Item *ItemsModel::item(int row)
{
	return Accessor<Item>().value(row);
}

QVariant ItemsModel::displayRoleData(int row, int column, Triple pointer) const
{
	const Item *item = accessor.value(row);

	switch (column)
	{
		case 0: return item->id;
		case 1: return item->iconIndex;
		case 2: return item->name;
		case Item::EFFECTS: return effectsData(item, pointer.row, pointer.column);
	}

	return QVariant();
}

QVariant ItemsModel::editRoleData(int row, int column, Triple pointer) const
{
	const Item *item = accessor.value(row);

	switch (column)
	{
		case Item::ID: return item->id;
		case Item::ANIMATION_ID: return item->animationId;
		case Item::CONSUMABLE: return item->consumable;
		case Item::DAMAGE_CRITICAL: return item->damage.critical;
		case Item::DAMAGE_ELEMENT: return item->damage.elementId + 1;
		case Item::DAMAGE_FORMULA: return item->damage.formula;
		case Item::DAMAGE_TYPE: return item->damage.type;
		case Item::DAMAGE_VARIANCE: return item->damage.variance;
		case Item::DESC: return item->description;
		case Item::EFFECTS: return effectsData(item, pointer.row, pointer.column);
		case Item::HIT_TYPE: return item->hitType;
		case Item::ICON_INDEX: return item->iconIndex;
		case Item::ITEM_TYPE: return item->itypeId - 1;
		case Item::NAME: return item->name;
		case Item::NOTE: return item->note;
		case Item::OCCASION: return item->occasion;
		case Item::PRICE: return item->price;
		case Item::REPEAT: return item->repeats;
		case Item::SCOPE: return item->scope;
		case Item::SPEED: return item->speed;
		case Item::SUCCESS: return item->successRate;
		case Item::TP_GAIN: return item->tpGain;
	}

	qDebug() << "ItemModel::editRoleData column" << column << "does not exist";
	return QVariant();
}

QVariant ItemsModel::userRoleData(int row, int column, Triple pointer) const
{
	Q_UNUSED(pointer);
	const Item *item = accessor.value(row);

	switch (column)
	{
		case Item::EFFECTS: return int(item->effects.size());
	}

	return QVariant();
}

void ItemsModel::setEditRoleData(int row, int column, const QVariant &value, Triple pointer)
{
	Q_UNUSED(pointer);
	Item *item = accessor.value(row);

	switch (column)
	{
		case Item::ID: item->id = value.toInt(); break;
		case Item::ANIMATION_ID: item->animationId = value.toInt(); break;
		case Item::CONSUMABLE: item->consumable = value.toInt(); break;
		case Item::DAMAGE_CRITICAL: item->damage.critical = value.toInt(); break;
		case Item::DAMAGE_ELEMENT: item->damage.elementId = value.toInt() - 1; break;
		case Item::DAMAGE_FORMULA: item->damage.formula = value.toString(); break;
		case Item::DAMAGE_TYPE: item->damage.type = value.toInt(); break;
		case Item::DAMAGE_VARIANCE: item->damage.variance = value.toInt(); break;
		case Item::DESC: item->description = value.toString(); break;
		case Item::EFFECTS: qDebug() << "setEditRoleData EFFECTS"; break;
		case Item::HIT_TYPE: item->hitType = value.toInt(); break;
		case Item::ICON_INDEX: item->iconIndex = value.toInt(); updateDisplayRole(index(row, 1)); break;
		case Item::ITEM_TYPE: item->itypeId = value.toInt() + 1; break;
		case Item::NAME: item->name = value.toString(); updateDisplayRole(index(row, 2)); break;
		case Item::NOTE: item->note = value.toString(); break;
		case Item::OCCASION: item->occasion = value.toInt(); break;
		case Item::PRICE: item->price = value.toInt(); break;
		case Item::REPEAT: item->repeats = value.toInt(); break;
		case Item::SCOPE: item->scope = value.toInt(); break;
		case Item::SPEED: item->speed = value.toInt(); break;
		case Item::SUCCESS: item->successRate = value.toInt(); break;
		case Item::TP_GAIN: item->tpGain = value.toInt(); break;
		default: qDebug() << "ItemModel::setDataFromMapper column" << column << "does not exist";
	}

	if (column == Item::DAMAGE_FORMULA && item->damage.formula.isEmpty())
		item->damage.formula = "0";
}





QVariant ItemsModel::effectsData(const Item *item, int row, int column) const
{
	const Effect *effect = &item->effects.at(row);
	switch (column)
	{
		case 0: return effectType(effect);
		case 1: return effectValue(effect);
		default: return QVariant();
	}
}

void ItemsModel::addEffect(int itemIndex)
{
	item(itemIndex)->effects.emplace_back();
	updateDisplayRole(index(itemIndex, Item::EFFECTS));
}

void ItemsModel::setEffect(int itemIndex, int effectIndex, Effect &&effect)
{
	item(itemIndex)->effects.at(effectIndex) = effect;
	updateDisplayRole(index(itemIndex, Item::EFFECTS));
}

void ItemsModel::removeEffect(int itemIndex, int effectIndex)
{
	item(itemIndex)->effects.erase(item(itemIndex)->effects.begin() + effectIndex);
	updateDisplayRole(index(itemIndex, Item::EFFECTS));
}



