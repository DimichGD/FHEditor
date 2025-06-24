#pragma once
#include "base_command.hpp"

struct Command_102: ICommandParams
{
	QStringList choices;
	int value_0; // cancel (-2: add Cancel barnch, -1: Disallow, 0..5: #1-#6)
	int value_1; // default (0: None, 0..5: #1-#6)
	int value_2; // windowPosition
	int value_3; // background

	Command_102() = default;
	Command_102(QStringList choices, int value_0,
				int value_1, int value_2, int value_3);

	int code() override { return 102; }
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;

	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
