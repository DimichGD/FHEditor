#pragma once
#include <QString>
#include <list>

struct Settings
{
	struct Game
	{
		QString name {};
		QString path {};
	};

	std::list<Game> gamesList {};
	QString lastPath {};
	QString rpgmPath {};

	int lastTabIndex = 0;
	int mapToolIndex = 0;
	int lastMapId = 0;

	static Settings *Get();

	bool load();
	bool save();
};

