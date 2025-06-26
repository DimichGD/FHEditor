#pragma once
#include "trait.hpp"
#include <QString>
#include <vector>
#include <array>

struct Armor
{
	int id;
	int atypeId = 0;
	QString description {};
	int etypeId = 2;
	std::vector<Trait> traits { { 22, 1, 0.0f } };
	int iconIndex = 0;
	QString name {};
	QString note {};
	std::array<int, 8> params {};
	int price = 0;
};
