#include "command_353.hpp"

#include <QDebug>
#include <QStringList>

void Command_353::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Game Over", ConstantColors::lightBlue);
}
