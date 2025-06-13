#pragma once
#include "base_command.hpp"
#include "event.hpp"

struct Command_250: ICommand
{
	Sound sound;

	Command_250(Sound sound);
	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
	static Command_250 parse(const std::string &parameters);
};
