#pragma once
#include "base_command.hpp"

struct Command_353: ICommandParams
{
	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
