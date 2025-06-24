#include "command_102.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

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

QString Command_102::backgroundToString()
{
	switch (value_3)
	{
		case 0: return "Window";
		case 1: return "Dim";
		case 2: return "Transparent";
	}
	return "Unknown";
}

QString Command_102::windowPositionToString()
{
	switch (value_2)
	{
		case 0: return "Left";
		case 1: return "Middle";
		case 2: return "Right";
	}
	return "Unknown";
}


void Command_102::read(JsonValue &parameters)
{
	choices = parameters[0].toStringList();
	value_0 = std::get<double>(parameters[1].data);
	value_1 = std::get<double>(parameters[2].data);
	value_2 = std::get<double>(parameters[3].data);
	value_3 = std::get<double>(parameters[4].data);
}

std::string Command_102::write()
{
	std::vector<std::string> temp;
	for (auto &s: choices)
		temp.push_back(s.toStdString());

	std::tuple<std::vector<std::string>, int, int, int, int> params;
	params = std::tie(temp, value_0, value_1, value_2, value_3);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void Command_102::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Show Choices: ", ConstantColors::purple);

	/*QStringList stringList;
	for (auto &s: choices)
		stringList.append(QString::fromStdString(s));*/

	drawText(painter, selected, rect, choices.join(", "), ConstantColors::blue);

	QString str = QString(" (%1, %2, #%3, #%4)")
			.arg(backgroundToString(), windowPositionToString())
			.arg(value_1)
			.arg(value_0);
	drawText(painter, selected, rect, str, ConstantColors::grey);
}
