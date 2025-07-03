#pragma once
#include "trait.hpp"
#include <QString>
#include <vector>
#include <array>

struct Weapon
{
	enum Type
	{
		ID, ANIMATION_ID, DESC, ETYPE_ID, ICON_INDEX, NAME, NOTE,
		/* PARAMS */
		PRICE, WTYPE_ID, COUNT,
	};

	int id;
	int animationId = 0;
	QString description {};
	int etypeId = 1;
	std::vector<Trait> traits { { 31, 1, 0.0f }, { 22, 0, 0.0f } }; // FIXME: do i need this default?
	int iconIndex = 0;
	QString name {};
	QString note {};
	std::array<int, 8> params {};
	int price = 0;
	int wtypeId = 0;
};
