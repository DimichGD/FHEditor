#include "command_230.hpp"

#include "glaze/json/read.hpp"

#include <QDebug>

Command_230::Command_230(int frames)
{
	this->frames = frames;
}

void Command_230::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString str = QString("Wait: %1 frames")
			.arg(frames);
	drawText(painter, selected, rect, str, ConstantColors::red);
}
