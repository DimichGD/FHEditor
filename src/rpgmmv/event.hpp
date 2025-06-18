#pragma once
#include "base_command.hpp"
#include <vector>
#include <list>

struct Command
{
	using It = std::list<Command>::iterator;

	int code;
	int indent;
	QSharedPointer<ICommandParams> parameters;
};

struct Event
{
	enum Type
	{
		ID, NAME, SWITCH_ID, TRIGGER,
	};

	int id;
	std::list<Command> list {};
	QString name {};
	int switchId = 0;
	int trigger = 0;
};

struct Condition
{
	int actorId = 1;
	bool actorValid = false;
	int itemId = 1;
	bool itemValid = false;
	QString selfSwitchCh { 'A' };
	bool selfSwitchValid = false;
	int switch1Id = 1;
	bool switch1Valid = false;
	int switch2Id = 1;
	bool switch2Valid = false;
	int variableId = 1;
	bool variableValid = false;
	int variableValue = 0;
};

struct Image
{
	int tileId;
	std::string characterName;
	int characterIndex;
	int direction;
	int pattern;
};

/*struct RouteEntry1
{
	int code;
	std::vector<int> parameters;
};

struct RouteEntry2
{
	int code;
	std::optional<int> indent;
};

struct RouteEntry3
{
	int code;
	std::vector<int> parameters;
	std::optional<int> indent;
};*/

struct Route
{
	std::string parseLater { R"({"list":[{"code":0,"parameters":[]}],"repeat":true,"skippable":false,"wait":false})" };
};


struct Page
{
	enum Type
	{
		COND_ACTOR_ID, COND_ACTOR_VALID,
		COND_ITEM_ID, COND_ITEM_VALID,
		COND_SELF_SWITCH_CHAR, COND_SELF_SWITCH_VALID,
		COND_SWITCH_1_ID, COND_SWITCH_1_VALID,
		COND_SWITCH_2_ID, COND_SWITCH_2_VALID,
		COND_VARIABLE_ID, COND_VARIABLE_VALID, COND_VARIABLE_VALUE,
		DIRECTION_FIX, /* IMAGE */
		MOVE_FREQ, MOVE_SPEED, MOVE_TYPE, PRIORITY_TYPE, STEP_ANIME,
		THROUGH, TRIGGER, WALK_ANIME, COUNT,
	};

	Condition conditions;
	bool directionFix;
	Image image;
	std::list<Command> list;
	int moveFrequency;
	Route moveRoute;
	int moveSpeed;
	int moveType;
	int priorityType;
	bool stepAnime;
	bool through;
	int trigger;
	bool walkAnime;
};

struct MapEvent
{
	int id;
	QString name;
	QString note;
	std::vector<Page> pages;
	int x;
	int y;
};
