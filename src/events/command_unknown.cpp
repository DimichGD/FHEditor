#include "command_unknown.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

Command_Unknown::Command_Unknown(int code)
{
	this->commandCode = code;
}

void Command_Unknown::prepare(const QFontMetrics &metrics)
{
	QString text = QString("Unknown Command %1: %2")
			.arg(commandCode)
			.arg(QString::fromStdString(write()));

	paintData.push_back({ text, ConstantColors::grey, metrics.horizontalAdvance(text) });
}

void Command_Unknown::read(JsonValue &parameters)
{
	this->parameters = parameters;
}

std::string Command_Unknown::write()
{
	return glz::write_json(parameters).value();
}

