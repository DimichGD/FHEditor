#pragma once
#include "base_command.hpp"

struct Command_000: ICommandParams
{
	Command_000() = default;

	int code() override { return 0; }
	int flags() override { return CAN_ADD; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override { (void)parameters; };
	auto write() -> std::string override { return "[]"; };
};
