#pragma once
#include "trait.hpp"
#include <string>
#include <vector>
#include <array>

struct Armor
{
	int id;
	int atypeId = 0;
	std::string description {};
	int etypeId = 2;
	std::vector<Trait> traits { { 22, 1, 0.0f } };
	int iconIndex = 0;
	std::string name {};
	std::string note {};
	std::array<int, 8> params {};
	int price = 0;
};
