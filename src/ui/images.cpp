#include "images.hpp"
#include "settings.hpp"
#include <QDir>
#include <QBuffer>
#include <QImageReader>

Images *Images::Get()
{
	static Images images;
	return &images;
}

bool Images::load()
{
	if (Settings::Get()->lastPath.isEmpty())
		return false;

	path = Settings::Get()->lastPath + "/img/";
	QDir imgDir(path);
	if (!imgDir.exists())
		return false;

	iconSetPixmap = loadImage("system/IconSet");

	return true;
}

QPixmap Images::loadImage(const QString &name)
{
	QString pngFilename = path + name + ".png";
	QFile pngFile(pngFilename);
	if (pngFile.exists())
		return QPixmap(pngFilename);

	int headerLen = 16;
	QByteArray pngHeader = QByteArray::fromHex("89504E470D0A1A0A0000000D49484452");
	//QString key = settings.value("key").toString();
	QString encFilename = path + name + ".rpgmvp";
	QFile encFile(encFilename);
	if (!encFile.exists())
	{
		qDebug() << encFilename << "does not exists";
		return QPixmap();
	}

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
		return QPixmap(); // TODO: make some error strings, maybe use std::expected

	return QPixmap::fromImageReader(&reader);
	/*QPixmap *pixmap = new QPixmap();
	*pixmap = QPixmap::fromImageReader(&reader);
	return pixmap;*/
}

QPixmap &Images::iconSet()
{
	//return loadImage("system/IconSet");
	return iconSetPixmap;
}

QPixmap Images::face(const QString &name)
{
	return loadImage("faces/" + name);
}

QPixmap Images::tileSet(const QString &name)
{
	return loadImage("tilesets/" + name);
}

QPixmap Images::animation(const QString &name)
{
	return loadImage("animations/" + name);
}
