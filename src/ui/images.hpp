#pragma once
#include <QString>
#include <QPixmap>
#include <map>

class Images
{
public:
	static Images *Get();
	bool load();
	QPixmap *loadImage(const QString &name);

	QPixmap *iconSet();
	QPixmap *face(const QString &name);
	QPixmap *tileSet(const QString &name);
	QPixmap *animation(const QString &name);

private:
	QString path {};
	QPixmap *iconSetPixmap = nullptr;
	std::map<QString, QPixmap> cache;
};

