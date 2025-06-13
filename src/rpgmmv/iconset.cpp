#include "iconset.hpp"
#include "images.hpp"
#include <QFile>
#include <QPixmapCache>
#include <QDebug>

bool IconSet::load()
{
	iconset = Images::Get()->iconSet();
	if (iconset.isNull())
		return false;

	return true;

	/*if (!QFile::exists(filename))
		return false;

	if (!iconset.load(filename))
		return false;*/

	return true;
}

QPixmap &IconSet::get(int index)
{
	if (cache.contains(index))
		return cache[index];

	int y = index / 16; // TODO: Check boundaries
	int x = index % 16;

	cache.insert(index, iconset.copy(QRect(x * 32, y * 32, 32, 32)));
	return cache[index];
}

QPixmap &IconSet::pixmap()
{
	return iconset;
}

IconSet *IconSet::Get()
{
	static IconSet iconset;
	return &iconset;
}
