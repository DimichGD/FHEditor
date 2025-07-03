#pragma once
//#include "base_command.hpp"
#include <QModelIndex>
#include <QString>
//#include <QObject>
#include <list>


class ICommandParams;

struct Command
{
	using Iterator = std::list<Command>::iterator;

	int code = 0;
	int indent = 0;
	std::shared_ptr<ICommandParams> parameters;

	Command() = default;
	Command(int code, int indent, std::shared_ptr<ICommandParams> parameters)
	{
		this->code = code;
		this->indent = indent;
		this->parameters = parameters;
	}

	static Iterator iteratorFromIndex(const QModelIndex &index);
	static Command makeZeroCommand(int indent);
};

struct Event
{
	enum Type
	{
		ID, NAME, SWITCH_ID, TRIGGER, COUNT
	};

	int id;
	std::list<Command> list {};
	QString name {};
	int switchId = 0;
	int trigger = 0;
};
