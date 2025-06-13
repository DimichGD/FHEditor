#pragma once
#include "trait.hpp"
#include <QString>
#include <optional>
#include <vector>

struct State
{
	int id;
	int autoRemovalTiming = 0;
	int chanceByDamage = 100;
	std::optional<QString> description { std::nullopt };
	std::optional<std::vector<Trait>> traits { std::nullopt };
	int iconIndex = 0;
	int maxTurns = 1;
	QString message1 {};
	QString message2 {};
	QString message3 {};
	QString message4 {};
	int minTurns = 1;
	int motion = 0;
	QString name {};
	QString note {};
	int overlay = 0;
	int priority = 50;
	std::optional<bool> releaseByDamage { std::nullopt };
	bool removeAtBattleEnd = false;
	bool removeByDamage = false;
	bool removeByRestriction = false;
	bool removeByWalking = false;
	int restriction = 0;
	int stepsToRemove = 100;
};
