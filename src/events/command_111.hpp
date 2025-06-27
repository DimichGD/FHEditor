#pragma once
#include "base_command.hpp"

struct Command_111: ICommandParams
{
	enum Type
	{
		SWITCH, VARIABLE, SELF_SWITCH, TIMER,
		ACTOR, //ACTOR_IN_PARTY, ACTOR_NAME,
		ENEMY, CHARACTER, VEHICLE,
		GOLD, ITEM, WEAPON, ARMOR, BUTTON, SCRIPT,
	};

	JsonValue condData;

	Command_111() = default;
	Command_111(JsonValue condData) { this->condData = condData; }

	int code() override { return 111; }
	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; }

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;


};

