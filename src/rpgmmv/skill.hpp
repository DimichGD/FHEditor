#pragma once
#include "effect.hpp"
#include "damage.hpp"

struct Skill
{
	enum Type
	{
		ID, ANIMATION_ID,
		DAMAGE_CRITICAL,
		DAMAGE_ELEMENT,
		DAMAGE_FORMULA,
		DAMAGE_TYPE,
		DAMAGE_VARIANCE,
		DESC, HIT_TYPE, ICON_INDEX, MESSAGE1, MESSAGE2,
		MP_COST, NAME, NOTE, OCCASION, REPEAT, REQ_WTYPE_ID1, REQ_WTYPE_ID2,
		SCOPE, SPEED, STYPE_ID, SUCCESS, TP_COST, TP_GAIN, COUNT,
	};

	int id;
	int animationId = 0;
	Damage damage {};
	QString description {};
	std::vector<Effect> effects {};
	int hitType = 0;
	int iconIndex = 0;
	QString message1 {};
	QString message2 {};
	int mpCost = 0;
	QString name {};
	QString note {};
	int occasion = 0;
	int repeats = 1;
	int requiredWtypeId1 = 0;
	int requiredWtypeId2 = 0;
	int scope = 1;
	int speed = 0;
	int stypeId = 1;
	int successRate = 100;
	int tpCost = 0;
	int tpGain = 0;
};
