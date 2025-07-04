#pragma once
#include "base_command.hpp"

struct Command_Unknown: ICommandParams
{
	Command_Unknown(int code);

	int commandCode;
	JsonValue parameters;

	int code() override { return commandCode; }
	int flags() override { return 0; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	std::string write() override;
};
