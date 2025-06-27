#pragma once
#include "base_command.hpp"

struct CommandComment: ICommandParams
{
	QString line;

	CommandComment() = default;
	CommandComment(QString line);

	int code() override { return 108; }
	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;
};
