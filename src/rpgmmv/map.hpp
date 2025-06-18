#pragma once
#include "event.hpp"
#include "sound.hpp"

struct Map
{
	bool autoplayBgm;
	bool autoplayBgs;
	QString battleback1Name;
	QString battleback2Name;
	Sound bgm;
	Sound bgs;
	bool disableDashing;
	QString displayName;
	std::vector<int> encounterList; // FIXME: int is not a correct type
	int encounterStep;
	int height;
	QString note;
	bool parallaxLoopX;
	bool parallaxLoopY;
	QString parallaxName;
	bool parallaxShow;
	int parallaxSx;
	int parallaxSy;
	int scrollType;
	bool specifyBattleback;
	int tilesetId;
	int width;
	std::vector<int> data;
	std::vector<std::optional<MapEvent>> events;
};
