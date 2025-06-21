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
	MOVIE,
	BGM = 241, BGS = 245, ME = 249, SE = 250,
};

class DirectoryListView: public QListView
{
	Q_OBJECT

public:
	DirectoryListView(QWidget *parent = nullptr): QListView(parent) {}
	void setMode(PickerType type, QString itemName);
	QString path();

private:
	QDir dir;
	QStandardItemModel *model = nullptr;
};

