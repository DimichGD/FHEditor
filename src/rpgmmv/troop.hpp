#pragma once
#include "event.hpp"

struct Troop
{
	struct Condition
	{
		int actorHp = 50;
		int actorId = 1;
		int actorValid = false;
		int enemyHp = 50;
		int enemyIndex = 1;
		int enemyValid = false;
		int switchId = 1;
		bool switchValid = false;
		int turnA = 0;
		int turnB = 0;
		bool turnEnding = false;
		bool turnValid = false;
	};

	struct Page
	{
		Condition conditions {};
		std::list<Command> list { Command::makeZeroCommand(0) };
		int span = 0;
	};

	struct Member
	{
		int enemyId = 1;
		int x = 0;
		int y = 0;
		bool hidden = false;
	};

	int id;
	std::vector<Member> members {};
	std::vector<Condition> pages { {} };
};
