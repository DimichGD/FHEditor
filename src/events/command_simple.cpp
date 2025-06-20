#include "command_simple.hpp"


void CommandSimple::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	switch (codeVar)
	{
		case 112: drawText(painter, selected, rect, "Loop", ConstantColors::blue); break;
		case 113: drawText(painter, selected, rect, "Break Loop", ConstantColors::blue); break;
		case 217: drawText(painter, selected, rect, "Gather Followers", ConstantColors::darkRed); break;
		case 251: drawText(painter, selected, rect, "Stop SE", ConstantColors::cyan); break;
		case 352: drawText(painter, selected, rect, "Open Save Screen", ConstantColors::lightBlue); break;
		case 353: drawText(painter, selected, rect, "Game Over", ConstantColors::lightBlue); break;
		case 404: drawText(painter, selected, rect, "End Choices", ConstantColors::purple); break;
		case 411: drawText(painter, selected, rect, "Else", ConstantColors::blue); break;
		case 412: drawText(painter, selected, rect, "End If", ConstantColors::blue); break;
		case 413: drawText(painter, selected, rect, "Repeat Loop", ConstantColors::blue); break;
	}
}
