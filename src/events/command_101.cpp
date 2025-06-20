#include "command_101.hpp"
#include "json_qstring.hpp"

#include <QDebug>

Command_101_Params::Command_101_Params(QString faceName, int faceIndex, int background, int windowPosition)
{
	this->faceName = faceName;
	this->faceIndex = faceIndex;
	this->background = background;
	this->windowPosition = windowPosition;
}

QString Command_101_Params::backgroundToString()
{
	switch (background)
	{
		case 0: return "Window";
		case 1: return "Dim";
		case 2: return "Transparent";
	}
	return "Unknown";
}

QString Command_101_Params::windowPositionToString()
{
	switch (windowPosition)
	{
		case 0: return "Top";
		case 1: return "Middle";
		case 2: return "Bottom";
	}
	return "Unknown";
}

QString Command_101_Params::faceToString()
{
	if (faceName.isEmpty())
		return "Null";

	//QString actualFaceName = faceName.isEmpty() ? "Null" : faceName;
	return QString("%1(%2)").arg(faceName).arg(faceIndex);
}

void Command_101_Params::read(const std::string &parameters)
{
	std::tuple<QString, int, int, int> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	faceName = std::get<0>(params);
	faceIndex = std::get<1>(params);
	background = std::get<2>(params);
	windowPosition = std::get<3>(params);
}

std::string Command_101_Params::write()
{
	std::tuple<QString, int, int, int> params;
	params = std::tie(faceName, faceIndex, background, windowPosition);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void Command_101_Params::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Text: ", ConstantColors::purple);

	QString str = QString("%1, %2, %3")
			.arg(faceToString(), backgroundToString(), windowPositionToString());
	drawText(painter, selected, rect, str, ConstantColors::grey);
}
