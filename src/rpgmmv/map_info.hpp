#pragma once
#include <QString>

struct MapInfo
{
	enum Type
	{
		ID, EXPANDED, NAME, ORDER, PARENT_ID, SCROLL_X, SCROLL_Y, COUNT,
	};

	int id;
	bool expanded = false;
	QString name {};
	int order = 0;
	int parentId = 0;
	double scrollX = 659;
	double scrollY = 371;
	//bool quick; // Look Outside
};
