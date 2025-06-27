#pragma once
//#include "base_command.hpp"
#include <QModelIndex>
#include <QString>
#include <QObject>
#include <list>


class ICommandParams;

struct Command
{
	using Iterator = std::list<Command>::iterator;

	//Q_DISABLE_COPY(Command)

	int code = 0;
	int indent = 0;
	std::shared_ptr<ICommandParams> parameters;
	//QSharedPointer<ICommandParams> parameters;

	Command() = default;
	Command(int code, int indent, std::shared_ptr<ICommandParams> parameters)
	{
		this->code = code;
		this->indent = indent;
		this->parameters = parameters;
	}

	/*Command() = default;
	Command(int code, int indent, ICommandParams *parameters)
	{
		this->code = code;
		this->indent = indent;
		this->parameters = parameters;
	}
	~Command();
	Command(Command &&other)
	{
		std::swap(code, other.code);
		std::swap(indent, other.indent);
		std::swap(parameters, other.parameters);
	}
	Command &operator=(Command &&other)
	{
		std::swap(code, other.code);
		std::swap(indent, other.indent);
		std::swap(parameters, other.parameters);
		return *this;
	}*/
	static Iterator iteratorFromIndex(const QModelIndex &index);
	static Command makeZeroCommand(int indent);
};

struct Event
{
	enum Type
	{
		ID, NAME, SWITCH_ID, TRIGGER,
	};

	int id;
	std::list<Command> list {};
	QString name {};
	int switchId = 0;
	int trigger = 0;
};
