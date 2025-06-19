#pragma once
#include "event.hpp"
#include "base_command.hpp"
//#include "command_101.hpp"
//#include "command_unknown.hpp"

#include <QPainter>

class CommandFactory
{
public:
	template<typename T, typename ...Args>
	static QSharedPointer<ICommandParams> createCommand(Args&& ...args)
	{
		return QSharedPointer<ICommandParams>(new T(std::forward<Args>(args)...));
	}

	static QSharedPointer<ICommandParams> createCommand2(int code);

	enum Code
	{
		ZERO = 0,
		TEXT = 101,
		BEGIN_CHOICES = 102,
		IF = 111,
		PLAY_BGM = 241,
		PLAY_BGS = 245,
		PLAY_ME = 249,
		PLAY_SE = 250,
		LINE = 401,
		END_CHOICES = 404,
		ELSE = 411,
		END_IF = 412,
	};
};
