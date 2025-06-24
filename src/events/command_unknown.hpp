#pragma once
#include "base_command.hpp"

struct Command_Unknown: ICommandParams
{
	Command_Unknown(int codeId);

	int codeId;
	//std::string parameters;
	JsonValue parameters;

	int code() override { return codeId; }
	void read(JsonValue &parameters) override;
	std::string write() override;

	int flags() override { return 0; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
