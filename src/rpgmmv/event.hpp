#pragma once
#include "base_command.hpp"
#include "command_factory.hpp"
#include "json_value.hpp"
#include <QAbstractItemModel>
#include <vector>
#include <list>

struct Command
{
	using Iterator = std::list<Command>::iterator;

	static Iterator iteratorFromIndex(const QModelIndex &index)
	{
		return index.data(Qt::UserRole + 1).value<Command::Iterator>();
	}

	static Command makeZeroCommand(int indent)
	{
		return { CommandFactory::ZERO, indent, CommandFactory::createCommand2(0) };
	}

	int code;
	int indent;
	QSharedPointer<ICommandParams> parameters;
	//std::vector<glz::json_t> jsonValues;
	//JsonValue jsonValues;
	//CommandParams parameters;

	void readParams(JsonValue &&jsonValues)
	{
		parameters = CommandFactory::createCommand2(code);
		parameters->read(jsonValues);
	}

	/*JsonValue &writeParams()
	{
		return jsonValues;
	}*/
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
