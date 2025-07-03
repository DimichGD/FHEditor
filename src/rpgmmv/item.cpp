#include "item.hpp"

/*QVariant Item::toVariant(int column) const
{
	switch (column)
	{
		case Item::ID: return id;
		case Item::ANIMATION_ID: return animationId;
		case Item::CONSUMABLE: return consumable;
		case Item::DAMAGE_CRITICAL: return damage.critical;
		case Item::DAMAGE_ELEMENT: return damage.elementId + 1;
		case Item::DAMAGE_FORMULA: return damage.formula;
		case Item::DAMAGE_TYPE: return damage.type;
		case Item::DAMAGE_VARIANCE: return damage.variance;
		case Item::DESC: return description;
		case Item::EFFECTS: return QVariant::fromValue(&effects);
		case Item::HIT_TYPE: return hitType;
		case Item::ICON_INDEX: return iconIndex;
		case Item::ITEM_TYPE: return itypeId - 1;
		case Item::NAME: return name;
		case Item::NOTE: return note;
		case Item::OCCASION: return occasion;
		case Item::PRICE: return price;
		case Item::REPEAT: return repeats;
		case Item::SCOPE: return scope;
		case Item::SPEED: return speed;
		case Item::SUCCESS: return successRate;
		case Item::TP_GAIN: return tpGain;
		default: qDebug() << "Item::toVariant column" << column << "does not exist";
	}

	return QVariant();
}

void Item::fromVariant(int column, const QVariant &value)
{
	switch (column)
	{
		case Item::ID: id = value.toInt(); break; // FIXME: id should never change
		case Item::ANIMATION_ID: animationId = value.toInt(); break;
		case Item::CONSUMABLE: consumable = value.toInt(); break;
		case Item::DAMAGE_CRITICAL: damage.critical = value.toInt(); break;
		case Item::DAMAGE_ELEMENT: damage.elementId = value.toInt() - 1; break;
		case Item::DAMAGE_FORMULA: damage.formula = value.toString(); break;
		case Item::DAMAGE_TYPE: damage.type = value.toInt(); break;
		case Item::DAMAGE_VARIANCE: damage.variance = value.toInt(); break;
		case Item::DESC: description = value.toString(); break;
		case Item::EFFECTS: qDebug() << "Item::fromVariant"; break;
		case Item::HIT_TYPE: hitType = value.toInt(); break;
		case Item::ICON_INDEX: iconIndex = value.toInt(); break;
		case Item::ITEM_TYPE: itypeId = value.toInt() + 1; break;
		case Item::NAME: name = value.toString(); break;
		case Item::NOTE: note = value.toString(); break;
		case Item::OCCASION: occasion = value.toInt(); break;
		case Item::PRICE: price = value.toInt(); break;
		case Item::REPEAT: repeats = value.toInt(); break;
		case Item::SCOPE: scope = value.toInt(); break;
		case Item::SPEED: speed = value.toInt(); break;
		case Item::SUCCESS: successRate = value.toInt(); break;
		case Item::TP_GAIN: tpGain = value.toInt(); break;
		default: qDebug() << "Item::fromVariant column" << column << "does not exist";
	}

	if (column == Item::DAMAGE_FORMULA && damage.formula.isEmpty())
		damage.formula = "0";
}*/
