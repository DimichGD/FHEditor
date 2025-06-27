#pragma once
#include "effect.hpp"
#include "damage.hpp"

struct Item
{
	enum Type
	{
		ID, ANIMATION_ID, CONSUMABLE,
		DAMAGE_CRITICAL,
		DAMAGE_ELEMENT,
		DAMAGE_FORMULA,
		DAMAGE_TYPE,
		DAMAGE_VARIANCE,
		DESC, EFFECTS, HIT_TYPE, ICON_INDEX, ITEM_TYPE, NAME, NOTE,
		OCCASION, PRICE, REPEAT, SCOPE, SPEED, SUCCESS, TP_GAIN,
		COUNT,
	};

	int id;
	int animationId = 0;
	bool consumable = false;
	Damage damage {};
	QString description {};
	std::vector<Effect> effects {};
	int hitType = 0;
	int iconIndex = 0;
	int itypeId = 1;
	QString name {};
	QString note {};
	int occasion = 0;
	int price = 0;
	int repeats = 1;
	int scope = 0;
	int speed = 0;
	int successRate = 100;
	int tpGain = 0;
};

