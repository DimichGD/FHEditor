#include "event_content_selection_model.hpp"
#include "command_factory.hpp"
#include "event.hpp"

void EventContentSelectionModel::select(const QItemSelection &selection, SelectionFlags flags)
{
	if (!(flags & Select))
	{
		QItemSelectionModel::select(selection, flags);
		return;
	}

	if (selection.empty())
		return;

	if (selection[0].indexes().empty())
		return;

	enum Strategy { SELECT_UNTIL, SELECT_WHILE };
	struct Holder { int endCode; Strategy strategy; };
	static std::map<int, Holder> codesMap = {
		{ CommandFactory::TEXT,          { CommandFactory::TEXT_LINE,    SELECT_WHILE } },
		{ CommandFactory::COMMENT,       { CommandFactory::COMMENT_LINE, SELECT_WHILE } },
		{ CommandFactory::BEGIN_CHOICES, { CommandFactory::END_CHOICES,  SELECT_UNTIL } },
		{ CommandFactory::IF,            { CommandFactory::END_IF     ,  SELECT_UNTIL } },
		{ CommandFactory::LOOP,          { CommandFactory::REPEAT_LOOP,  SELECT_UNTIL } },
		//{ 402, { 0, SELECT_UNTIL, true } },
		//{ 411, { 0, SELECT_UNTIL, true } },
	};

	QItemSelection rowSelection;
	QModelIndex first = selection[0].indexes()[0];
	QModelIndex last = selection[0].indexes()[0];

	Command::Iterator command = Command::iteratorFromIndex(first);
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

	std::advance(command, 1);
	while (true)
	{
		last = model()->index(last.row() + 1, 0);
		if (strategy == SELECT_WHILE
			&& std::next(command)->code != endCode)
			break;

		if (strategy == SELECT_UNTIL
			&& command->code == endCode
			&& command->indent == startIndent)
			break;

		std::advance(command, 1);
	}

	rowSelection.select(first, last);
	QItemSelectionModel::select(rowSelection, flags);
}
