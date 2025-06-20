#pragma once
#include <QString>
#include <vector>

struct TileSet
{
	enum Set
	{
		A1, A2, A3, A4, A5,
		B, C, D, E, COUNT,
	};

	int id;
	std::vector<int> flags;
	int mode;
	QString name;
	QString note;
	std::vector<QString> tilesetNames;
};
