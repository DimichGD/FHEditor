#pragma once
#include "trait.hpp"
#include <QString>
#include <array>

struct Actor
{
	int id;
	QString battlerName {};
	int characterIndex = 0;
	QString characterName {};
	int classId = 1;
	std::array<int, 5> equips {};
	int faceIndex = 0;
	QString faceName {};
	std::vector<Trait> traits {};
	int initialLevel = 1;
	int maxLevel = 99;
	QString name {};
	QString nickname {};
	QString note {};
	QString profile {};
};
