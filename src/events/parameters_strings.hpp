#pragma once
#include <QString>

struct ToString
{
	static QString background(int index);
	static QString windowVPosition(int index);
	static QString windowHPosition(int index);
	static QString face(QString name, int index);
};
