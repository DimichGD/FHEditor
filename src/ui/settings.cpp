#include "settings.hpp"

#include <QSettings>

Settings *Settings::Get()
{
	static Settings settings;
	return &settings;
}

bool Settings::load()
{
	QSettings settings("settings.ini", QSettings::Format::IniFormat);
	if (!settings.isWritable())
	{
		qDebug() << "settings.ini is not writable";
		return false;
	}

	lastPath = settings.value("lastPath").toString();
	rpgmPath = settings.value("rpgmPath").toString();

	settings.beginGroup("Games");
	int arrayLength = settings.beginReadArray("game");
	gamesList.reserve(arrayLength);

	for (int i = 0; i < arrayLength; i++)
	{
		settings.setArrayIndex(i);
		QString name = settings.value("name").toString();
		QString path = settings.value("path").toString();

		if (settings.status() != QSettings::NoError)
		{
			qDebug() << "Failed to read settings.ini" << settings.status();
			return false;
		}

		gamesList.append({ name, path });
	}

	settings.endArray();
	settings.endGroup();

	if (settings.status() != QSettings::NoError)
	{
		qDebug() << "Failed to read settings.ini" << settings.status();
		return false;
	}

	return true;
}

bool Settings::save()
{
	QSettings settings("settings.ini", QSettings::Format::IniFormat);
	if (!settings.isWritable())
	{
		qDebug() << "settings.ini is not writable";
		return false;
	}

	settings.beginGroup("Games");
	settings.remove("");
	settings.beginWriteArray("game");
	for (int i = 0; i < gamesList.count(); i++)
	{
		settings.setArrayIndex(i);
		settings.setValue("name", gamesList.at(i).name);
		settings.setValue("path", gamesList.at(i).path);
	}

	settings.endArray();
	settings.endGroup();

	settings.setValue("lastPath", lastPath);
	settings.setValue("rpgmPath", rpgmPath);
	settings.sync();

	if (settings.status() != QSettings::NoError)
	{
		qDebug() << "Failed to write settings.ini" << settings.status();
		return false;
	}

	return false;
}
