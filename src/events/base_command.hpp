#pragma once

#include <QString>
#include <QPainter>
#include <QSharedPointer>

struct ICommand
{
	virtual ~ICommand() = default;
	virtual int code() { return -1; };
	virtual void drawImpl(QPainter *painter, bool selected, QRect &rect) = 0;
	virtual void read(const std::string &parameters) { (void)parameters; }
	virtual auto write() -> std::string { return "[]"; };

	virtual bool canAdd() { return false; }
	virtual bool canEdit() { return false; }
	virtual bool canDelete() { return false; }

	void draw(QPainter *painter, bool selected, QRect rect, int indent)
	{
		int textAdvance = 8 + indent * 32;
		rect.adjust(textAdvance, 0, 0, 0);
		drawImpl(painter, selected, rect);
	}

	void drawText(QPainter *painter, bool selected, QRect &rect, const QString &text, QColor color)
	{
		QPen pen = painter->pen();
		if (selected)
			pen.setColor(QColorConstants::White);
		else
			pen.setColor(color);
		painter->setPen(pen);
		painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, text);

		int textAdvance = painter->fontMetrics().horizontalAdvance(text);
		rect.adjust(textAdvance, 0, 0, 0);
	}
};

struct ConstantColors
{
	static constexpr QColor purple    { QColor::Rgb, 255 * 0x101,  77 * 0x101,  10 * 0x101, 138 * 0x101 };
	static constexpr QColor grey      { QColor::Rgb, 255 * 0x101, 130 * 0x101, 133 * 0x101, 136 * 0x101 };
	static constexpr QColor blue      { QColor::Rgb, 255 * 0x101,   4 * 0x101,  10 * 0x101, 135 * 0x101 };
	static constexpr QColor red       { QColor::Rgb, 255 * 0x101, 223 * 0x101,  47 * 0x101,  83 * 0x101 };
	static constexpr QColor cyan      { QColor::Rgb, 255 * 0x101,   8 * 0x101, 135 * 0x101, 136 * 0x101 };
	static constexpr QColor green     { QColor::Rgb, 255 * 0x101,  14 * 0x101, 141 * 0x101,  48 * 0x101 };
	static constexpr QColor orange    { QColor::Rgb, 255 * 0x101, 242 * 0x101, 160 * 0x101,  17 * 0x101 };
	static constexpr QColor shit      { QColor::Rgb, 255 * 0x101, 134 * 0x101, 131 * 0x101,   3 * 0x101 };
	static constexpr QColor darkRed   { QColor::Rgb, 255 * 0x101, 175 * 0x101,  38 * 0x101,  26 * 0x101 };
	static constexpr QColor lightBlue { QColor::Rgb, 255 * 0x101,  72 * 0x101, 157 * 0x101, 254 * 0x101 };
};
