#include "event.hpp"
#include "command_factory.hpp"
#include <QModelIndex>

/*Command::~Command()
{
	//if (parameters)
		delete parameters;
}*/

Command Command::makeZeroCommand(int indent)
{
	return { CommandFactory::ZERO, indent, CommandFactory::createCommand2(0) };
}

Command::Iterator Command::iteratorFromIndex(const QModelIndex &index)
{
	return index.data(Qt::UserRole + 1).value<Command::Iterator>();
}

