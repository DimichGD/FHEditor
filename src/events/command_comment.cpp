#include "command_comment.hpp"
#include "json_qstring.hpp"
#include <QDebug>

CommandComment::CommandComment(QString line)
{
	this->line = line;
}

void CommandComment::read(JsonValue &parameters)
{
	line = parameters[0].toQString();
}

std::string CommandComment::write()
{
	std::tuple<QString> params;
	params = std::tie(line);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void CommandComment::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Comment: ", ConstantColors::green);
	drawText(painter, selected, rect, line, ConstantColors::green);
}




CommandCommentLine::CommandCommentLine(QString line)
{
	this->line = line;
}


void CommandCommentLine::read(JsonValue &parameters)
{
	line = parameters[0].toQString();
}

std::string CommandCommentLine::write()
{
	std::tuple<QString> params;
	params = std::tie(line);
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(params);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}

void CommandCommentLine::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "       : ", ConstantColors::green);
	drawText(painter, selected, rect, line, ConstantColors::green);
}



