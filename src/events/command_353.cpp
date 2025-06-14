#include "command_353.hpp"

#include <QDebug>
#include <QStringList>

void Command_353::drawImpl(QPainter *painter, bool selected, QRect &rect)
{
	drawText(painter, selected, rect, "Game Over", ConstantColors::lightBlue);
}

Command_353 Command_353::parse(const std::string &parameters)
{
	if (parameters != "[]")
		qDebug() << "Parameters is not [], it's" << QString::fromStdString(parameters);

	return {};
}
