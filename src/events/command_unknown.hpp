#pragma once
#include "base_command.hpp"

struct Command_Unknown: ICommand
{
	Command_Unknown(int codeId);

	int codeId;
	std::string parameters;

	int code() override { return codeId; }
	void read(const std::string &str) override;
	std::string write() override;

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
