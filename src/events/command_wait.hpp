#pragma once
#include "base_command.hpp"

struct CommandWait: ICommandParams
{
	int frames = 0;

	CommandWait() = default;
	CommandWait(int frames);

	int code() override { return 230; };
	int flags() override  { return CAN_ADD | CAN_EDIT | CAN_DELETE; }

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;
};
