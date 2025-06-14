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

Command_230 Command_230::parse(const std::string &parameters)
{
	std::tuple<int> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	return std::make_from_tuple<Command_230>(params);
}
