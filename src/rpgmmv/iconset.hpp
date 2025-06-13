#pragma once
#include <QString>
#include <QPixmap>
#include <QMap>

class IconSet
{
public:
	bool load();
	QPixmap &get(int index);
	QPixmap &pixmap();

	static IconSet *Get();

private:
	QPixmap iconset;
	QMap<int, QPixmap> cache;
};

