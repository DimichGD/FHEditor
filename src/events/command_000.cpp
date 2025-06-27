#include "command_000.hpp"

void Command_000::prepare(const QFontMetrics &metrics)
{
	paintData.push_back({ "-", QColorConstants::Black, metrics.horizontalAdvance("-") });
}
