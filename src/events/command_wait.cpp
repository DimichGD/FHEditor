#include "command_wait.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

CommandWait::CommandWait(int frames)
{
	this->frames = frames;
}

void CommandWait::prepare(const QFontMetrics &metrics)
{
	QString text = QString("Wait: %1 frames").arg(frames);
	paintData.push_back({ text, ConstantColors::red, metrics.horizontalAdvance(text) });
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
