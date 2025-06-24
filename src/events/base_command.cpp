#include "base_command.hpp"
#include "glaze/core/reflect.hpp"
#include <QDebug>

void ICommandParams::draw(QPainter *painter, bool selected, QRect rect, int indent)
{
	int textAdvance = 8 + indent * 32;
	rect.adjust(textAdvance, 0, 0, 0);
	drawImpl(painter, selected, rect);
}

void ICommandParams::drawText(QPainter *painter, bool selected, QRect &rect, const QString &text, QColor color)
{
	QPen pen = painter->pen();
	pen.setColor(selected ? QColorConstants::White : color);

	painter->setPen(pen);
	painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, text);

	int textAdvance = painter->fontMetrics().horizontalAdvance(text);
	rect.adjust(textAdvance, 0, 0, 0);
}

std::string ICommandParams::checkExpected(glz::expected<std::string, glz::error_ctx> result)
{
	if (!result.has_value())
	{
		qWarning() << QString::fromStdString(glz::format_error(result.error(), std::string {}));
		return "";
	}

	return result.value();
}
