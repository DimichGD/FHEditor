#include "command_000.hpp"

void Command_000::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "-", QColorConstants::Black);
}
