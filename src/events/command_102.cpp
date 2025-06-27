#include "command_102.hpp"
#include "parameters_strings.hpp"
#include "json_qstring.hpp"

#include <QDebug>
#include <QStringList>

Command_102::Command_102(QStringList choices, int value_0,
						 int value_1, int value_2, int value_3)
{
	this->choices = choices;
	this->value_0 = value_0;
	this->value_1 = value_1;
	this->value_2 = value_2;
	this->value_3 = value_3;
}

void Command_102::prepare(const QFontMetrics &metrics)
{
	QString text = QString(" (%1, %2, #%3, #%4)")
			.arg(ToString::background(value_3), ToString::windowHPosition(value_2))
			.arg(value_1)
			.arg(value_0);

	QString choicesText = choices.join(", ");

	paintData.reserve(3);
	paintData.push_back({ "Show Choices: ", ConstantColors::purple, metrics.horizontalAdvance("Show Choices: ") });
	paintData.push_back({ choicesText, ConstantColors::blue, metrics.horizontalAdvance(choicesText) });
	paintData.push_back({ text, ConstantColors::grey, metrics.horizontalAdvance(text) });
}


void Command_102::read(JsonValue &parameters)
{
	choices = parameters[0].toStringList();
	value_0 = parameters[1].toInt();
	value_1 = parameters[2].toInt();
	value_2 = parameters[3].toInt();
	value_3 = parameters[4].toInt();
}

std::string Command_102::write()
{
	std::vector<std::string> temp;
	for (auto &s: choices)
		temp.push_back(s.toStdString());

	auto params = std::tie(temp, value_0, value_1, value_2, value_3);
	return checkExpected(glz::write_json(params));
}
