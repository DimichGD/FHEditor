#pragma once
#include "trait.hpp"
#include <QString>
#include <array>

struct Action
{
	int conditionParam1 = 0;
	int conditionParam2 = 0;
	int conditionType = 0;
	int rating = 5;
	int skillId = 1;
};

struct DropItem
{
	int dataId = 1;
	int denominator = 1;
	int kind = 0;
};

struct Enemy
{
	int id;
	std::vector<Action> actions {};
	int battlerHue = 0;
	QString battlerName {};
	std::array<DropItem, 3> dropItems {};
	int exp = 0;
	std::vector<Trait> traits {};
	int gold = 0;
	QString name {};
	QString note {};
	std::array<int, 8> params { 100, 0, 10, 10, 10, 10, 10, 10 };
};
