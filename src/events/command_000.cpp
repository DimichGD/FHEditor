#include "command_000.hpp"
//#include <QColor>

void Command_000::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "-", QColorConstants::Black);
}
