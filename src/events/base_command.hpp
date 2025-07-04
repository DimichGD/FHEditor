#pragma once
#include "glaze/core/context.hpp"
#include "glaze/util/expected.hpp"
#include "json_value.hpp"
#include <QString>
#include <QPainter>

struct ICommandParams
{
	struct TextColor
	{
		QString text;
		QColor color;
		int advance;
	};

	enum Flags
	{
		CAN_ADD    = 1 << 0,
		CAN_EDIT   = 1 << 1,
		CAN_DELETE = 1 << 2,
		ALL = CAN_ADD | CAN_EDIT | CAN_DELETE
	};

	virtual ~ICommandParams() = default;
	virtual int code() { return -1; };
	virtual int flags() = 0;

	virtual void prepare(const QFontMetrics &metrics) = 0;
	virtual void read(JsonValue &parameters) = 0;
	virtual auto write() -> std::string = 0;

	int width(int indent);
	void draw(QPainter *painter, bool selected, QRect rect, int indent);

	std::vector<TextColor> paintData {};
};

std::string checkExpected(const glz::expected<std::string, glz::error_ctx> &result);

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
