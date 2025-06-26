#pragma once
#include "base_command.hpp"
//#include "event.hpp"

struct CommandWait: ICommandParams
{
	int frames = 0;

	CommandWait() = default;
	CommandWait(int frames);
	int code() override { return 230; };

	void read(JsonValue &parameters) override;
	auto write() -> std::string override;
	int flags() override  { return CAN_ADD | CAN_EDIT | CAN_DELETE; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
