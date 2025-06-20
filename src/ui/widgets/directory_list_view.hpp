#pragma once

#include <QDir>
#include <QListView>
#include <QStandardItemModel>

enum PickerType
{
	ICON_SET,
	FACE,
	ACTOR,
	ENEMY,
	BATTLE_BACK_1,
	BATTLE_BACK_2,
	PARALLAX,
	CHARACTER,
	TILESET,
	BGM, BGS, ME, SE,
	MOVIE,
};

class DirectoryListView: public QListView
{
	Q_OBJECT

public:
	DirectoryListView(QWidget *parent = nullptr): QListView(parent) {}
	void setMode(PickerType type, QString itemName);

private:
	QDir dir;
	QStandardItemModel *model = nullptr;
};

