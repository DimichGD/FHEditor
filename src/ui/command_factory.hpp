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
	static QSharedPointer<ICommand> createCommand(Args&& ...args)
	{
		return QSharedPointer<ICommand>(new T(std::forward<Args>(args)...));
	}

	static QSharedPointer<ICommand> createCommand2(int code);

	enum Code
	{
		ZERO = 0,
		TEXT = 101,
		BEGIN_CHOICES = 102,
		LINE = 401,
		END_CHOICES = 404,
	};
};

/*struct ColoredString
{
	QString string;
	QColor color;
};

class EventConverter
{
public:
	ColoredString codeToString(int code);

private:
	QColor purple = QColor::fromRgb(77, 10, 138);
	QColor grey = QColor::fromRgb(130, 133, 136);
	QColor blue = QColor::fromRgb(4, 10, 135);
	QColor red = QColor::fromRgb(223, 47, 83);
	QColor cyan = QColor::fromRgb(8, 135, 136);
	QColor green = QColor::fromRgb(14, 141, 48);
	QColor orange = QColor::fromRgb(242, 160, 17);
	QColor shit = QColor::fromRgb(134, 131, 3);
	QColor darkRed = QColor::fromRgb(175, 38, 26);
	QColor lightBlue = QColor::fromRgb(72, 157, 254);
};*/

