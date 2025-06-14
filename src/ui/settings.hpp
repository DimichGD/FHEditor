#pragma once
#include <QObject>
#include <QString>
#include <QList>

class Settings: public QObject
{
	Q_OBJECT

public:
	struct Game
	{
		QString name {};
		QString path {};
	};

	QList<Game> gamesList {};
	QString lastPath {};
	QString rpgmPath {};

	Settings(QObject *parent = nullptr): QObject(parent) {}
	static Settings *Get();

	bool load();
	bool save();

/*signals:
	void gameEntryAdded(QString name, QString path);
	void gameEntryRemoved(int index);*/
};

