#pragma once
#include "base_command.hpp"
#include "sound.hpp"
#include <optional>
#include <vector>
#include <list>

struct Command
{
	using It = std::list<Command>::iterator;

	int code;
	int indent;
	QSharedPointer<ICommand> parameters;
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
	int actorId;
	bool actorValid;
	int itemId;
	bool itemValid;
	QString selfSwitchCh;
	bool selfSwitchValid;
	int switch1Id;
	bool switch1Valid;
	int switch2Id;
	bool switch2Valid;
	int variableId;
	bool variableValid;
	int variableValue;
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
	std::string parseLater;
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
