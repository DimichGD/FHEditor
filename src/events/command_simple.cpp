#include "command_simple.hpp"

int CommandSimple::flags()
{
	switch (commandCode)
	{
		case 112: return CAN_ADD | CAN_DELETE;
		case 113: return CAN_ADD | CAN_DELETE;
		case 217: return CAN_ADD | CAN_DELETE;
		case 251: return CAN_ADD | CAN_DELETE;
		case 352: return CAN_ADD | CAN_DELETE;
		case 353: return CAN_ADD | CAN_DELETE;
		case 404: return 0;
		case 411: return 0;
		case 412: return 0;
		case 413: return 0;
	}

	return 0;
}

void CommandSimple::prepare(const QFontMetrics &metrics)
{
	QString text;
	QColor color;

	switch (commandCode)
	{
		case 112: text = "Loop"; color = ConstantColors::blue; break;
		case 113: text = "Break Loop"; color = ConstantColors::blue; break;
		case 217: text = "Gather Followers"; color = ConstantColors::darkRed; break;
		case 251: text = "Stop SE"; color = ConstantColors::cyan; break;
		case 352: text = "Open Save Screen"; color = ConstantColors::lightBlue; break;
		case 353: text = "Game Over"; color = ConstantColors::lightBlue; break;
		case 404: text = "End Choices"; color = ConstantColors::purple; break;
		case 411: text = "Else"; color = ConstantColors::blue; break;
		case 412: text = "End If"; color = ConstantColors::blue; break;
		case 413: text = "Repeat Loop"; color = ConstantColors::blue; break;
	}

	paintData.push_back({ text, color, metrics.horizontalAdvance(text) });
}

