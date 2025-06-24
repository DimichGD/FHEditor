#include "command_230.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

Command_230::Command_230(int frames)
{
	this->frames = frames;
}

void Command_230::read(JsonValue &parameters)
{
	frames = parameters[0].toInt();
}

std::string Command_230::write()
{
	auto params = std::tie(frames);
	return checkExpected(glz::write_json(params));
}

void Command_230::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString str = QString("Wait: %1 frames").arg(frames);
	drawText(painter, selected, rect, str, ConstantColors::red);
}
