#pragma once
#include "base_command.hpp"

struct Command_000: ICommandParams
{
	Command_000() = default;

	int code() override { return 0; }
	void read(JsonValue &parameters) override { (void)parameters; };
	auto write() -> std::string override { return "[]"; };

	int flags() override { return CAN_ADD; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
