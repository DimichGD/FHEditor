#pragma once
#include "base_command.hpp"

struct CommandLine: ICommandParams
{
	QString line;
	int commandCode;

	CommandLine(int code);
	CommandLine(int code, QString line);

	int code() override { return commandCode; }
	int flags() override { return 0; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;
};
