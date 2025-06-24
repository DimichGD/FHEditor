#include "command_sound.hpp"
#include "json_qstring.hpp"

#include <QDebug>

CommandSound::CommandSound(Type type)
{
	this->type = type;
}

CommandSound::CommandSound(Type type, Sound sound)
{
	this->type = type;
	this->sound = sound;
}

void CommandSound::read(JsonValue &parameters)
{
	//sound = std::get<Sound>(parameters[0].data);
	sound.name = parameters[0]["name"].toQString();
	sound.pan = parameters[0]["pan"].toInt();
	sound.pitch = parameters[0]["pitch"].toInt();
	sound.volume = parameters[0]["volume"].toInt();
}

std::string CommandSound::write()
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

void CommandSound::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	switch (type)
	{
		case BGM: drawText(painter, selected, rect, "Play BGM: ", ConstantColors::cyan); break;
		case BGS: drawText(painter, selected, rect, "Play BGS: ", ConstantColors::cyan); break;
		case ME: drawText(painter, selected, rect, "Play ME: ", ConstantColors::cyan); break;
		case SE: drawText(painter, selected, rect, "Play SE: ", ConstantColors::cyan); break;
	}

	QString str = QString("%1, (%2, %3, %4)")
			.arg(sound.name)
			.arg(sound.volume)
			.arg(sound.pitch)
			.arg(sound.pan);
	drawText(painter, selected, rect, str, ConstantColors::cyan);
}


