#include "parameters_strings.hpp"

QString ToString::background(int index)
{
	switch (index)
	{
		case 0: return "Window";
		case 1: return "Dim";
		case 2: return "Transparent";
		default: return "Unknown background index";
	}
}

QString ToString::windowVPosition(int index)
{
	switch (index)
	{
		case 0: return "Top";
		case 1: return "Middle";
		case 2: return "Bottom";
		default: return "Unknown windowVPosition index";
	}
}

QString ToString::windowHPosition(int index)
{
	switch (index)
	{
		case 0: return "Left";
		case 1: return "Middle";
		case 2: return "Right";
		default: return "Unknown windowHPosition index";
	}
}

QString ToString::face(QString name, int index)
{
	if (name.isEmpty())
		return "Null";

	return QString("%1(%2)").arg(name).arg(index);
}

