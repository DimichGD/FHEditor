#pragma once
#include "sound.hpp"
#include <optional>
#include <vector>
#include <array>

struct Timing
{
	std::optional<int> conditions;
	std::array<int, 4> flashColor { 255, 255, 255, 255 };
	int flashDuration = 5;
	int flashScope = 0;
	int frame = 0;
	std::optional<Sound> se { std::nullopt };
};

struct Animation
{
	int id;
	int animation1Hue = 0;
	QString animation1Name {};
	int animation2Hue = 0;
	QString animation2Name {};
	std::vector<std::vector<std::array<float, 8>>> frames {};
	QString name {};
	int position = 1;
	std::vector<Timing> timings {};
};
