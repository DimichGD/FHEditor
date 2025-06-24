#include "command_unknown.hpp"
#include "glaze/json/write.hpp"

#include <QDebug>

Command_Unknown::Command_Unknown(int codeId)
{
	this->codeId = codeId;
}

void Command_Unknown::read(JsonValue &parameters)
{
	this->parameters = parameters; //parameters[0].get_string();
}

std::string Command_Unknown::write()
{
	return glz::write_json(parameters).value();
}

void Command_Unknown::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString str = QString("Unknown Command %1: %2")
			.arg(codeId)
			.arg(QString::fromStdString(write()));
	drawText(painter, selected, rect, str, ConstantColors::grey);
}

/*template<>
QSharedPointer<ICommand> parseCommand<Command_Unknown>(const std::string &parameters)
{
	return QSharedPointer<ICommand>(new Command_Unknown(-1, parameters));
}*/
