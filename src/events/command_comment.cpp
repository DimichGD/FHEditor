#include "command_comment.hpp"
#include "json_qstring.hpp"

CommandComment::CommandComment(QString line)
{
	this->line = line;
}

void CommandComment::prepare(const QFontMetrics &metrics)
{
	paintData.reserve(2);
	paintData.push_back({ "Comment: ", ConstantColors::green, metrics.horizontalAdvance("Comment: ") });
	paintData.push_back({ line, ConstantColors::green, metrics.horizontalAdvance(line) });
}

void CommandComment::read(JsonValue &parameters)
{
	line = parameters[0].toQString();
}

std::string CommandComment::write()
{
	auto params = std::tie(line);
	return checkExpected(glz::write_json(params));
}

