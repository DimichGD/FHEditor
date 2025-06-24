#include "command_101.hpp"
#include "parameters_strings.hpp"
#include "json_qstring.hpp"

#include <QDebug>

Command_101_Params::Command_101_Params(QString faceName, int faceIndex, int background, int windowPosition)
{
	this->faceName = faceName;
	this->faceIndex = faceIndex;
	this->background = background;
	this->windowPosition = windowPosition;
}

void Command_101_Params::read(JsonValue &parameters)
{
	faceName = parameters[0].toQString();
	faceIndex = parameters[1].toInt();
	background = parameters[2].toInt();
	windowPosition = parameters[3].toInt();
}

std::string Command_101_Params::write()
{
	//std::tuple<QString, int, int, int> params;
	auto params = std::tie(faceName, faceIndex, background, windowPosition);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	return checkExpected(result);
}

void Command_101_Params::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Text: ", ConstantColors::purple);

	QString str = QString("%1, %2, %3")
			.arg(ToString::face(faceName, faceIndex),
				 ToString::background(background),
				 ToString::windowVPosition(windowPosition));
	drawText(painter, selected, rect, str, ConstantColors::grey);
}
