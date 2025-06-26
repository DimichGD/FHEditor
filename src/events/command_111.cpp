#include "command_111.hpp"
#include "json_qstring.hpp"
#include "database.hpp"

#include <QDebug>

QString toggleToString(int toggle)
{
	return (toggle == 0) ? "ON" : "OFF";
}

QString signToString(int sign)
{
	switch (sign)
	{
		case 0: return "==";
		case 1: return ">=";
		case 2: return "<=";
		case 3: return ">";
		case 4: return "<";
		case 5: return "!=";
	}

	return "?";
}

QString switchCondToString(JsonValue &condData)
{
	int switchId = condData[1].toInt();
	int toggleIndex = condData[2].toInt();

	return QString("%1 Switch is %2")
			.arg(Database::Get()->switchName(switchId),
				 toggleToString(toggleIndex));
}

QString variableCondToString(JsonValue &condData)
{
	int variableId = condData[1].toInt();
	int signIndex = condData[4].toInt();
	int numberOrVariableId = condData[3].toInt();
	Database *db = Database::Get();

	if (condData[2].toInt() == 0)
	{
		return QString("%1 %2 %3")
				.arg(db->variableName(variableId), signToString(signIndex))
				.arg(numberOrVariableId);
	}
	else
	{
		return QString("%1 %2 %3")
				.arg(db->variableName(variableId),
					 signToString(signIndex),
					 db->variableName(numberOrVariableId));
	}
}

QString selfSwitchCondToString(JsonValue &condData)
{
	QString switchName = condData[1].toQString();
	int toggleIndex = condData[2].toInt();

	return QString("Self Switch %1 is %2")
			.arg(switchName, toggleToString(toggleIndex));
}

QString timerCondToString(JsonValue &condData)
{
	int timeInSeconds = condData[1].toInt();
	int toggleIndex = condData[2].toInt();

	return QString("Timer %1 %2 min %3 sec")
			.arg(toggleIndex ? "<=" : ">=")
			.arg(timeInSeconds / 60)
			.arg(timeInSeconds % 60);
}

void Command_111::calculateWidth(QFontMetrics &metrics, int indent)
{
	// FIXME: ffffuuuuuck
	QString result = "If: ";

	switch (Type(condData[0].toInt()))
	{
		case SWITCH: result += switchCondToString(condData); break;
		case VARIABLE: result += variableCondToString(condData); break;
		case SELF_SWITCH: result += selfSwitchCondToString(condData); break;
		case TIMER: result += timerCondToString(condData); break;
		default:
			result += "Unparsed";
	}

	int textAdvance = metrics.horizontalAdvance(result);
	totalWidth = 8 + indent * 32 + textAdvance + 16;
}

void Command_111::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString result = "If: ";

	switch (Type(condData[0].toInt()))
	{
		case SWITCH: result += switchCondToString(condData); break;
		case VARIABLE: result += variableCondToString(condData); break;
		case SELF_SWITCH: result += selfSwitchCondToString(condData); break;
		case TIMER: result += timerCondToString(condData); break;
		default:
			result += "Unparsed";
	}

	drawText(painter, selected, rect, result, ConstantColors::blue);
}

void Command_111::read(JsonValue &parameters)
{
	condData = parameters;
	//type = Type(condData[0].toInt());
}

std::string Command_111::write()
{
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(condData);
	return checkExpected(result);
}
