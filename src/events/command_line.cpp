#include "command_line.hpp"
#include "json_qstring.hpp"

CommandLine::CommandLine(int code)
{
	this->commandCode = code;
}

CommandLine::CommandLine(int code, QString line)
{
	this->commandCode = code;
	this->line = line;
}

void CommandLine::prepare(const QFontMetrics &metrics)
{
	paintData.reserve(2);
	paintData.push_back({ "    : ", ConstantColors::purple, metrics.horizontalAdvance("    : ") });
	paintData.push_back({ line, ConstantColors::blue, metrics.horizontalAdvance(line) });
}

void CommandLine::read(JsonValue &parameters)
{
	line = parameters[0].toQString();
}

std::string CommandLine::write()
{
	auto params = std::tie(line);
	return checkExpected(glz::write_json(params));
}
