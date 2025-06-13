#pragma once
#include <QString>

struct Damage
{
	bool critical = false;
	int elementId = 0;
	QString formula { "0" };
	int type = 0;
	int variance = 20;
};
