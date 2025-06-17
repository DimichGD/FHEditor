#include "command_250.hpp"
#include "json_qstring.hpp"

#include <QDebug>

Command_250::Command_250(Sound sound)
{
	this->sound = sound;
}

void Command_250::read(const std::string &parameters)
{
	std::tuple<Sound> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	sound = std::get<0>(params);
}

std::string Command_250::write()
{
	std::tuple<Sound> params = std::tie(sound);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void Command_250::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Play SE: ", ConstantColors::shit);

	QString str = QString("%1, (%2, %3, %4)")
			.arg(sound.name)
			.arg(sound.volume)
			.arg(sound.pitch)
			.arg(sound.pan);
	drawText(painter, selected, rect, str, ConstantColors::shit);
}
