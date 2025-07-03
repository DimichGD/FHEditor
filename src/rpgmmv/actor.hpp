#pragma once
#include "trait.hpp"
#include <QString>
#include <array>

struct Actor
{
	enum Type
	{
		ID, BATTLER_NAME, CHARACTER_INDEX, CHARACTER_NAME, CLASS_ID,
		/* EQUIP_0, ... */
		FACE_INDEX, FACE_NAME, INITIAL_LEVEL, MAX_LEVEL,
		NAME, NICKNAME, NOTE, PROFILE, COUNT,
	};

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
