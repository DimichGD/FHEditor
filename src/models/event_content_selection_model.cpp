#include "event_content_selection_model.hpp"
#include "command_factory.hpp"

/*void EventContentSelectionModel::select(const QModelIndex &index, SelectionFlags command)
{
	QItemSelectionModel::select(index, command);
}*/

void EventContentSelectionModel::select(const QItemSelection &selection, SelectionFlags flags)
{
	if (!(flags & Select))
	{
		QItemSelectionModel::select(selection, flags);
		return;
	}

	//QItemSelectionModel::select(selection, flags);

	if (selection.empty())
		return;

	if (selection[0].indexes().empty())
		return;

	enum Strategy { SELECT_UNTIL, SELECT_WHILE };
	struct Holder { int endCode; Strategy strategy; };
	static std::map<int, Holder> codesMap = {
		{ CommandFactory::TEXT,          { CommandFactory::LINE,        SELECT_WHILE } },
		{ CommandFactory::BEGIN_CHOICES, { CommandFactory::END_CHOICES, SELECT_UNTIL } },
		{ CommandFactory::IF,            { CommandFactory::END_IF     , SELECT_UNTIL } },
		//{ 402, { 0, SELECT_UNTIL, true } },
		//{ 411, { 0, SELECT_UNTIL, true } },
	};

	QItemSelection rowSelection;
	QModelIndex first = selection[0].indexes()[0];
	QModelIndex last = selection[0].indexes()[0];

	Command::It command = first.data(Qt::UserRole + 1).value<Command::It>();
	int startCode = command->code;
	int startIndent = command->indent;
	auto it = codesMap.find(startCode);
	if (it == codesMap.end())
	{
		QItemSelectionModel::select(selection, flags);
		return;
	}

	int endCode = it->second.endCode;
	Strategy strategy = it->second.strategy;

	//if (strategy == SELECT_WHILE)
	{
		std::advance(command, 1);
		while (true)
		{
			last = model()->index(last.row() + 1, 0);
			if (strategy == SELECT_WHILE && std::next(command)->code != endCode)
				break;

			if (strategy == SELECT_UNTIL && command->code == endCode && command->indent == startIndent)
				break;
			//if (std::next(command)->code != endCode)
			//	break;

			std::advance(command, 1);
		}
	}

	/*if (strategy == SELECT_UNTIL)
	{
		std::advance(command, 1);
		while (true)
		{
			last = model()->index(last.row() + 1, 0);
			if (command->code == endCode && command->indent == startIndent)
				break;

			std::advance(command, 1);
		}
	}*/

	/*do
	{
		std::advance(command, 1);
		last = model()->index(last.row() + 1, 0);
	}
	while ((strategy == SELECT_WHILE)
		   ? (command->code == endCode)
		   : (command->code != endCode));*/

	/*if (!it->second.consumeLast)
	{
		std::advance(command, -1);
		last = model()->index(last.row() - 1, 0);
	}*/

	rowSelection.select(first, last);
	QItemSelectionModel::select(rowSelection, flags);
}
