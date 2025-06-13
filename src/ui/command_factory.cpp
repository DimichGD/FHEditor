#include "command_factory.hpp"
#include "command_000.hpp"
#include "command_101.hpp"
#include "command_102.hpp"
#include "command_230.hpp"
#include "command_250.hpp"
#include "command_353.hpp"
#include "command_401.hpp"
#include "command_404.hpp"
#include "command_unknown.hpp"

#include <QDebug>

/*ColoredString EventConverter::codeToString(int code)
{
	switch (code)
	{
		case 000: return { "-", QColorConstants::Black };
		//case 101: return { "Text: ", purple };
		//case 102: return { "Show Choices: ", purple };
		case 108: return { "Comment: ", green };
		case 111: return { "If: ", blue };
		case 117: return { "Common Event: ", blue };
		case 121: return { "Switch: ", red };
		case 122: return { "Variables: ", red };
		case 126: return { "Change item: ", orange };
		case 212: return { "Show Animation: ", darkRed };
		case 223: return { "Tint Screen: ", shit };
		//case 230: return { "Wait: ", red };
		case 231: return { "Show Picture: ", purple };
		case 232: return { "Move Picture: ", purple };
		case 235: return { "Erase Picture: ", purple };
		//case 250: return { "Play Sound: ", cyan };
		//case 353: return { "Game Over. ", lightBlue };
		case 356: return { "Plugin: ", purple };
		//case 401: return { "    : ", grey };
		case 402: return { "When: ", purple }; // when choice
		case 404: return { "End choices. ", purple };
		case 411: return { "Else: ", purple };
		case 412: return { "End If. ", purple };
	}

	return { "Unknown: ", QColorConstants::Black };
}*/


QSharedPointer<ICommand> CommandFactory::createCommand2(int code)
{
	QSharedPointer<ICommand> command;

	switch (code)
	{
		case ZERO:           command = createCommand<Command_000>(); break;
		case TEXT:           command = createCommand<Command_101>(); break;
		case BEGIN_CHOICES:  command = createCommand<Command_102>(); break;
		case LINE:           command = createCommand<Command_401>(); break;
		case END_CHOICES:    command = createCommand<Command_404>(); break;
		default:             command = createCommand<Command_Unknown>(code); break;
	}

	return command;
}

