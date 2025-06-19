#include "command_simple.hpp"


void CommandSimple::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	switch (codeVar)
	{
		case 404: drawText(painter, selected, rect, "End Choices", ConstantColors::purple); break;
		case 411: drawText(painter, selected, rect, "Else", ConstantColors::blue); break;
		case 412: drawText(painter, selected, rect, "End If", ConstantColors::blue); break;
	}
}
