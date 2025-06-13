#pragma once
#include "trait.hpp"
#include <string>
#include <vector>
#include <array>

struct Weapon
{
	int id;
	int animationId = 0;
	std::string description {};
	int etypeId = 1;
	std::vector<Trait> traits { { 31, 1, 0.0f }, { 22, 0, 0.0f } };
	int iconIndex = 0;
	std::string name {};
	std::string note {};
	std::array<int, 8> params {};
	int price = 0;
	int wtypeId = 0;
};
