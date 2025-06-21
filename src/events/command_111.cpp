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

QString switchCondToString(std::vector<std::variant<double, std::string, bool>> &condData)
{
	int switchId = std::get<double>(condData[1]);
	int toggleIndex = std::get<double>(condData[2]);

	return QString("%1 Switch is %2")
			.arg(Database::Get()->switchName(switchId),
				 toggleToString(toggleIndex));
}

QString variableCondToString(std::vector<std::variant<double, std::string, bool>> &condData)
{
	int variableId = std::get<double>(condData[1]);
	int signIndex = std::get<double>(condData[4]);
	int numberOrVariableId = std::get<double>(condData[3]);
	Database *db = Database::Get();

	if (std::get<double>(condData[2]) == 0)
	{
		return QString("%1 %2 %3")
				.arg(db->variableName(variableId), signToString(signIndex))
				.arg(numberOrVariableId);

		// return QString("%1 %2 %3").arg(p[1].asVar).arg(p[4].asArr(signArray)).arg(p[3].asInt);
		// return makeString<_, Var, _, int, Arr<signArray>>("%1 %3 %2");
	}
	else
	{
		return QString("%1 %2 %3")
				.arg(db->variableName(variableId),
					 signToString(signIndex),
					 db->variableName(numberOrVariableId));
	}
}

QString selfSwitchCondToString(std::vector<std::variant<double, std::string, bool>> &condData)
{
	QString switchName = QString::fromStdString(std::get<std::string>(condData[1]));
	int toggleIndex = std::get<double>(condData[2]);

	return QString("Self Switch %1 is %2")
			.arg(switchName, toggleToString(toggleIndex));
}

QString timerCondToString(std::vector<std::variant<double, std::string, bool>> &condData)
{
	int timeInSecs = std::get<double>(condData[1]);
	int toggleIndex = std::get<double>(condData[2]);
	int mins = timeInSecs / 60;
	int secs = timeInSecs % 60;

	return QString("Timer %1 %2 min %3 sec")
			.arg(toggleIndex ? "<=" : ">=")
			.arg(mins)
			.arg(secs);
}

void Command_111::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString result = "If: ";

	switch (type)
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

void Command_111::read(const std::string &parameters)
{
	glz::error_ctx err = glz::read_json(condData, parameters);
	if (err)
		qDebug() << QString::fromStdString(parameters) << QString::fromStdString(glz::format_error(err));

	type = Type(std::get<double>(condData[0]));
}

void Command_111::read(const std::vector<glz::json_t> &parameters)
{
	for (size_t i = 0; i < parameters.size(); i++)
	{
		std::variant<double, std::string, bool> value;
		condData.push_back(glz::read_json<std::variant<double, std::string, bool>>(parameters[i]).value());
		/*if (parameters[i].holds<std::string>())
			qDebug()
					<< "String!!!"
					<< QString::fromStdString(parameters[i].as<std::string>())
					<< QString::fromStdString(std::get<std::string>(condData[i]));*/
	}

	type = Type(std::get<double>(condData[0]));
	//qDebug() << "stub";
}

std::string Command_111::write()
{
	glz::expected<std::string, glz::error_ctx> result = glz::write_json(condData);
	if (!result.has_value())
	{
		qDebug() << QString::fromStdString(glz::format_error(result.error()));
		return "";
	}

	return result.value();
}
