#pragma once
#include "base_command.hpp"

struct Command_401_Params: ICommandParams
{
	QString line;

	Command_401_Params() = default;
	Command_401_Params(QString line);

	int code() override { return 401; }
	void read(const std::string &str) override;
	auto write() -> std::string override;

	int flags() override { return 0; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
