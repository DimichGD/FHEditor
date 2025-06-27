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
	auto params = std::tie(faceName, faceIndex, background, windowPosition);
	return checkExpected(glz::write_json(params));
}

void Command_101_Params::prepare(const QFontMetrics &metrics)
{
	QString str = QString("%1, %2, %3")
			.arg(ToString::face(faceName, faceIndex),
				 ToString::background(background),
				 ToString::windowVPosition(windowPosition));

	paintData.reserve(2);
	paintData.push_back({ "Text: ", ConstantColors::purple, metrics.horizontalAdvance("Text: ") });
	paintData.push_back({ str, ConstantColors::grey, metrics.horizontalAdvance(str) });
}
