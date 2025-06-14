#include "command_401.hpp"

#include "glaze/json/read.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

namespace glz
{
	template<>
	struct from<JSON, QString>
	{
		template <auto Opts>
		static void op(QString& value, auto&&... args)
		{
			std::string buffer {};
			parse<JSON>::op<Opts>(buffer, args...);
			value = QString::fromStdString(buffer);
		}
	};

	template<>
	struct to<JSON, QString>
	{
		template <auto Opts>
		static void op(QString& value, auto&&... args)
		{
			std::string buffer = value.toStdString();
			serialize<JSON>::op<Opts>(buffer, args...);
		}
	};
}

Command_401::Command_401(QString line)
{
	this->line = line;
}

void Command_401::read(const std::string &str)
{
	std::tuple<QString> params;
	glz::error_ctx err = glz::read_json(params, str);
	if (err)
		qDebug() << QString::fromStdString(glz::format_error(err));

	line = std::get<0>(params);
}

std::string Command_401::write()
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


void Command_401::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "    : ", ConstantColors::purple);
	drawText(painter, selected, rect, line, ConstantColors::blue);
}

/*Command_401 Command_401::parse(const std::string &parameters)
{
	std::tuple<std::string> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << glz::format_error(err);

	return std::make_from_tuple<Command_401>(params);
}*/

/*template<>
QSharedPointer<ICommand> parseCommand<Command_401>(const std::string &parameters)
{
	std::tuple<std::string> params;
	glz::error_ctx err = glz::read_json(params, parameters);
	if (err)
		qDebug() << glz::format_error(err);

	return QSharedPointer<ICommand>(new Command_401(std::make_from_tuple<Command_401>(params)));
}*/

