#pragma once
#include <QString>

struct MapInfo
{
	int id;
	bool expanded = false;
	QString name {};
	int order = 0;
	int parentId = 0;
	double scrollX = 659;
	double scrollY = 371;
	//bool quick; // Look Outside
};
