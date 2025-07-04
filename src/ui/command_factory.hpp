#pragma once
#include "base_command.hpp"

class CommandFactory
{
public:
	/*template<typename T, typename ...Args>
	static QSharedPointer<ICommandParams> createCommand(Args&& ...args)
	{
		return QSharedPointer<ICommandParams>(new T(std::forward<Args>(args)...));
	}

	static QSharedPointer<ICommandParams> createCommand2(int code);*/

	template<typename T, typename ...Args>
	static std::shared_ptr<ICommandParams> createCommand(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	static std::shared_ptr<ICommandParams> createCommand2(int code);

	enum Code
	{
		ZERO = 0,
		TEXT = 101,
		BEGIN_CHOICES = 102,
		COMMENT = 108,
		IF = 111,
		LOOP = 112,
		BREAK_LOOP = 113,
		GATHER_FOLLOWERS = 217,
		WAIT = 230,
		PLAY_BGM = 241,
		PLAY_BGS = 245,
		PLAY_ME = 249,
		PLAY_SE = 250,
		STOP_SE = 251,
		OPEN_SAVE_SCREEN = 352,
		GAME_OVER = 353,
		TEXT_LINE = 401,
		END_CHOICES = 404,
		COMMENT_LINE = 408,
		ELSE = 411,
		END_IF = 412,
		REPEAT_LOOP = 413,
	};
};
