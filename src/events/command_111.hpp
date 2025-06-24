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

	/*std::array<int, 3> switchCond;
	std::array<int, 5> variableCond;
	std::tuple<int, QString, int> selfSwitchCond;
	std::array<int, 3> timerCond;
	std::array<int, 3> actorInPartyCond;*/
	Type type;
	JsonValue condData;

	int code() override { return 111; }

	Command_111() = default;

	void calculateWidth(QFontMetrics &metrics, int indent) override;
	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;

	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; }
};

