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

	//std::tuple<std::vector<std::string>, int, int, int, int> params;
	auto params = std::tie(temp, value_0, value_1, value_2, value_3);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	return checkExpected(result);
}

void Command_102::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Show Choices: ", ConstantColors::purple);

	/*QStringList stringList;
	for (auto &s: choices)
		stringList.append(QString::fromStdString(s));*/

	drawText(painter, selected, rect, choices.join(", "), ConstantColors::blue);

	QString str = QString(" (%1, %2, #%3, #%4)")
			.arg(ToString::background(value_3), ToString::windowHPosition(value_2))
			.arg(value_1)
			.arg(value_0);
	drawText(painter, selected, rect, str, ConstantColors::grey);
}
