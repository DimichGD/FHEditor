#include "images.hpp"
#include "settings.hpp"
#include <QDir>
#include <QBuffer>
#include <QImageReader>
#include <QMessageBox>

Images *Images::Get()
{
	static Images images;
	return &images;
}

bool Images::load()
{
	//iconSetPixmap = nullptr;
	cache.clear();

	if (Settings::Get()->lastPath.isEmpty())
		return false;

	path = Settings::Get()->lastPath + "/img/";
	if (!QDir(path).exists())
	{
		QMessageBox::critical(nullptr, "Filesystem Error", path + " does not exists.");
		return false;
	}

	iconSetPixmap = *loadImage("system/IconSet");

	return true;
}

QPixmap *Images::loadImage(const QString &name)
{
	auto it = cache.find(name);
	if (it != cache.end())
		return &it->second;

	QString pngFilename = path + name + ".png";
	if (QFile::exists(pngFilename))
	{
		cache[name] = QPixmap(pngFilename);
		return &cache[name];
	}

	int headerLen = 16;
	QByteArray pngHeader = QByteArray::fromHex("89504E470D0A1A0A0000000D49484452");
	//QString key = settings.value("key").toString();
	QString encFilename = path + name + ".rpgmvp";
	if (!QFile::exists(encFilename))
	{
		qDebug() << encFilename << "does not exists";
		return nullptr;
	}

	QFile encFile(encFilename);
	encFile.open(QIODevice::ReadOnly);
	encFile.skip(headerLen);
	QByteArray content = encFile.read(encFile.size() - headerLen);
	for(int i = 0; i < headerLen; i++)
	{
		//uint8_t byte = key.mid(i * 2, 2).toUInt(nullptr, 16);
		//content[i] = content[i] ^ byte;
		content[i] = pngHeader[i];
	}

	QBuffer buffer(&content);
	QImageReader reader(&buffer);
	if (!reader.canRead())
		return nullptr; // TODO: make some error strings, maybe use std::expected

	cache[name] = QPixmap::fromImageReader(&reader);
	return &cache[name];
}

QPixmap *Images::iconSet()
{
	return &iconSetPixmap;
}

QPixmap *Images::face(const QString &name)
{
	if (name.isEmpty())
		return nullptr;

	return loadImage("faces/" + name);
}

QPixmap Images::tileSet(const QString &name)
{
	if (name.isEmpty())
		return {};

	return *loadImage("tilesets/" + name);
}

QPixmap *Images::animation(const QString &name)
{
	if (name.isEmpty())
		return nullptr;

	return loadImage("animations/" + name);
}
