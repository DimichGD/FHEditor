#include "command_factory.hpp"
#include "command_000.hpp"
#include "command_101.hpp"
#include "command_102.hpp"
#include "command_111.hpp"
#include "command_wait.hpp"
#include "command_comment.hpp"
#include "command_simple.hpp"
#include "command_sound.hpp"
#include "command_line.hpp"
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


std::shared_ptr<ICommandParams> CommandFactory::createCommand2(int code)
//ICommandParams *CommandFactory::createCommand2(int code)
{
	//QSharedPointer<ICommandParams> command;
	std::shared_ptr<ICommandParams> command;

	switch (code)
	{
		case ZERO:             command = createCommand<Command_000>(); break;
		case TEXT:             command = createCommand<Command_101_Params>(); break;
		case BEGIN_CHOICES:    command = createCommand<Command_102>(); break;
		case COMMENT:          command = createCommand<CommandComment>(); break;
		case IF:               command = createCommand<Command_111>(); break;
		case LOOP:             command = createCommand<CommandSimple>(code); break;
		case BREAK_LOOP:       command = createCommand<CommandSimple>(code); break;
		case GATHER_FOLLOWERS: command = createCommand<CommandSimple>(code); break;
		case WAIT:             command = createCommand<CommandWait>(); break;
		case PLAY_BGM:         command = createCommand<CommandSound>(CommandSound::BGM); break;
		case PLAY_BGS:         command = createCommand<CommandSound>(CommandSound::BGS); break;
		case PLAY_ME:          command = createCommand<CommandSound>(CommandSound::ME); break;
		case PLAY_SE:          command = createCommand<CommandSound>(CommandSound::SE); break;
		case STOP_SE:          command = createCommand<CommandSimple>(code); break;
		case OPEN_SAVE_SCREEN: command = createCommand<CommandSimple>(code); break;
		case GAME_OVER:        command = createCommand<CommandSimple>(code); break;
		case TEXT_LINE:        command = createCommand<CommandLine>(code); break;
		case END_CHOICES:      command = createCommand<CommandSimple>(code); break;
		case COMMENT_LINE:     command = createCommand<CommandLine>(code); break;
		case ELSE:             command = createCommand<CommandSimple>(code); break;
		case END_IF:           command = createCommand<CommandSimple>(code); break;
		case REPEAT_LOOP:      command = createCommand<CommandSimple>(code); break;
		default:               command = createCommand<Command_Unknown>(code); break;
	}

	return command;
}

