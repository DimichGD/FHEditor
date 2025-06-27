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

void CommandSound::prepare(const QFontMetrics &metrics)
{
	QString command;
	switch (type)
	{
		case BGM: command = "Play BGM: "; break;
		case BGS: command = "Play BGS: "; break;
		case ME: command = "Play ME: "; break;
		case SE: command = "Play SE: "; break;
	}

	QString text = QString("%1, (%2, %3, %4)")
			.arg(sound.name)
			.arg(sound.volume)
			.arg(sound.pitch)
			.arg(sound.pan);

	paintData.push_back({ command, ConstantColors::cyan, metrics.horizontalAdvance(command) });
	paintData.push_back({ text, ConstantColors::cyan, metrics.horizontalAdvance(text) });
}

void CommandSound::read(JsonValue &parameters)
{
	sound.name = parameters[0]["name"].toQString();
	sound.pan = parameters[0]["pan"].toInt();
	sound.pitch = parameters[0]["pitch"].toInt();
	sound.volume = parameters[0]["volume"].toInt();
}

std::string CommandSound::write()
{
	auto params = std::tie(sound);
	return checkExpected(glz::write_json(params));
}
