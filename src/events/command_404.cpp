#include "command_404.hpp"
#include <QPainter>

void Command_404::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "End Choices", ConstantColors::purple);
}
