#pragma once
#include "trait.hpp"
#include <QString>
#include <vector>
#include <array>

struct Weapon
{
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
