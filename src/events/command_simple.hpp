#pragma once
#include "base_command.hpp"

struct CommandSimple: ICommandParams
{
	explicit CommandSimple(int code) { this->commandCode = code;  }

	int commandCode = -1;

	int code() override { return commandCode; }
	int flags() override;

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override { (void)parameters; }
	auto write() -> std::string override { return "[]"; };
};
