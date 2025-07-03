#pragma once
#include "trait.hpp"
#include <QString>
#include <array>

struct Learning
{
	int level = 1;
	QString note {};
	int skillId = 1;
};

struct Class
{
	enum Type
	{
		ID, NAME, NOTE, COUNT,
	};

	int id;
	std::array<int, 4> expParams { 30, 20, 30, 30 };
	std::vector<Trait> traits {};
	std::vector<Learning> learnings {};
	QString name {};
	QString note {};
	std::array<std::array<int, 100>, 8> params {};
};
