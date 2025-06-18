#pragma once
#include "base_command.hpp"
#include "event.hpp"

struct Command_230: ICommandParams
{
	int frames;

	Command_230(int frames);
	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
