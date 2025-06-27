#pragma once
#include "event.hpp"
#include "image.hpp"
#include "json_value.hpp"

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


struct Route
{
	// "list":[{"code":0,"parameters":[]}], ...
	JsonValue list { JsonValue::array_t { { JsonValue::object_t {
					{ "code", JsonValue { 0.0 } },
					{ "parameters", { JsonValue::array_t {} } }
				} } } };
	bool repeat = true;
	bool skippable = false;
	bool wait = false;
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

	Condition conditions {};
	bool directionFix = false;
	Image image {};
	std::list<Command> list { Command::makeZeroCommand(0) };
	int moveFrequency = 2;
	Route moveRoute {};
	int moveSpeed = 2;
	int moveType = 0;
	int priorityType = 0;
	bool stepAnime = false;
	bool through = false;
	int trigger = 1;
	bool walkAnime = true;
};

struct MapEvent
{
	int id;
	QString name {};
	QString note {};
	std::vector<Page> pages { {} };
	int x = 0;
	int y = 0;

	static QString makeName(int eventId)
	{
		return QString("EV%1").arg(eventId, 3, 10, QChar('0'));
	}

	static MapEvent makeDefault(int eventId, int x, int y)
	{
		MapEvent event
		{
			.id = eventId,
			.name = makeName(eventId),
			.x = x,
			.y = y,
		};

		return event;
	}
};
