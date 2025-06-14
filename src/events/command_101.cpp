#include "command_101.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

Command_101::Command_101(std::string faceName, int faceIndex, int background, int windowPosition)
{
	this->faceName = faceName;
	this->faceIndex = faceIndex;
	this->background = background;
	this->windowPosition = windowPosition;
}

QString Command_101::backgroundToString()
{
	switch (background)
	{
		case 0: return "Window";
		case 1: return "Dim";
		case 2: return "Transparent";
	}
	return "Unknown";
}

QString Command_101::windowPositionToString()
{
	switch (windowPosition)
	{
		case 0: return "Top";
		case 1: return "Middle";
		case 2: return "Bottom";
	}
	return "Unknown";
}

QString Command_101::faceToString()
{
	QString actualFaceName = faceName.empty() ? "Null" : QString::fromStdString(faceName);
	return QString("%1(%2)").arg(actualFaceName).arg(faceIndex);
}

void Command_101::read(const std::string &parameters)
{
	std::tuple<std::string, int, int, int> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	faceName = std::get<0>(params);
	faceIndex = std::get<1>(params);
	background = std::get<2>(params);
	windowPosition = std::get<3>(params);
}

std::string Command_101::write()
{
	std::tuple<std::string, int, int, int> params;
	params = std::tie(faceName, faceIndex, background, windowPosition);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void Command_101::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Text: ", ConstantColors::purple);

	QString str = QString("%1, %2, %3")
			.arg(faceToString(), backgroundToString(), windowPositionToString());
	drawText(painter, selected, rect, str, ConstantColors::grey);
}

/*template<>
QSharedPointer<ICommand> parseCommand<Command_101>(const std::string &parameters)
{
	std::tuple<std::string, int, int, int> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << glz::format_error(err);

	//return std::make_shared<Command_101>(std::make_from_tuple<Command_101>(params));
	return QSharedPointer<ICommand>(new Command_101(std::make_from_tuple<Command_101>(params)));
}*/

