#include "command_wait.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

CommandWait::CommandWait(int frames)
{
	this->frames = frames;
}

void CommandWait::read(JsonValue &parameters)
{
	frames = parameters[0].toInt();
}

std::string CommandWait::write()
{
	auto params = std::tie(frames);
	return checkExpected(glz::write_json(params));
}

void CommandWait::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString str = QString("Wait: %1 frames").arg(frames);
	drawText(painter, selected, rect, str, ConstantColors::red);
}
