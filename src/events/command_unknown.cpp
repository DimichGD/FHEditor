#include "command_unknown.hpp"

#include <QDebug>

/*Command_Unknown::Command_Unknown(int codeId)
{
	this->codeId = codeId;
}*/

Command_Unknown::Command_Unknown(int codeId)
{
	this->codeId = codeId;
	//this->parameters = parameters;
}

void Command_Unknown::read(const std::string &str)
{
	parameters = str;
}

std::string Command_Unknown::write()
{
	return parameters;
}

void Command_Unknown::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	QString str = QString("Unknown Command %1: %2")
			.arg(codeId)
			.arg(parameters);
	drawText(painter, selected, rect, str, ConstantColors::grey);
}

/*template<>
QSharedPointer<ICommand> parseCommand<Command_Unknown>(const std::string &parameters)
{
	return QSharedPointer<ICommand>(new Command_Unknown(-1, parameters));
}*/
