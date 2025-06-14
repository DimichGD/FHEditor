#include "command_250.hpp"

#include "glaze/json/read.hpp"

#include <QDebug>

namespace glz
{
	template<>
	struct from<JSON, QString>
	{
		template <auto Opts>
		static void op(QString& value, auto&&... args)
		{
			std::string buffer {};
			parse<JSON>::op<Opts>(buffer, args...);
			value = QString::fromStdString(buffer);
		}
	};
}

Command_250::Command_250(Sound sound)
{
	this->sound = sound;
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

Command_250 Command_250::parse(const std::string &parameters)
{
	std::tuple<Sound> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	return std::make_from_tuple<Command_250>(params);
}
