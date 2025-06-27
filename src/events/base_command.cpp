#include "base_command.hpp"
#include "glaze/core/reflect.hpp"
#include <QDebug>

int ICommandParams::width(int indent)
{
	int totalWidth = 8 + indent * 32;

	for (auto &data: paintData)
		totalWidth += data.advance;

	return totalWidth + 32;
}

void ICommandParams::draw(QPainter *painter, bool selected, QRect rect, int indent)
{
	int textAdvance = 8 + indent * 32;
	rect.adjust(textAdvance, 0, 0, 0);

	for (auto &data: paintData)
	{
		QPen pen = painter->pen();
		pen.setColor(selected ? QColorConstants::White : data.color);

		painter->setPen(pen);
		painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, data.text);

		rect.adjust(data.advance, 0, 0, 0);
	}
}



std::string checkExpected(const glz::expected<std::string, glz::error_ctx> &result)
{
	if (!result.has_value())
	{
		qWarning() << QString::fromStdString(glz::format_error(result.error(), std::string {}));
		return "";
	}

	return result.value();
}
