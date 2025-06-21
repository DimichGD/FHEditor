#include "command_comment.hpp"
#include "json_qstring.hpp"
#include <QDebug>

CommandComment::CommandComment(QString line)
{
	this->line = line;
}

void CommandComment::read(const std::string &str)
{
	std::tuple<QString> params;
	glz::error_ctx err = glz::read_json(params, str);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	line = std::get<0>(params);
}

void CommandComment::read(const std::vector<glz::json_t> &parameters)
{
	line = QString::fromStdString(parameters[0].as<std::string>());
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

void CommandCommentLine::read(const std::string &str)
{
	std::tuple<QString> params;
	glz::error_ctx err = glz::read_json(params, str);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	line = std::get<0>(params);
}

void CommandCommentLine::read(const std::vector<glz::json_t> &parameters)
{
	line = QString::fromStdString(parameters[0].as<std::string>());
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



