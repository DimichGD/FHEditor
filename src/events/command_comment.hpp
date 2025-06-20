#pragma once
#include "base_command.hpp"

struct CommandComment: ICommandParams
{
	QString line;

	CommandComment() = default;
	CommandComment(QString line);

	int code() override { return 108; }
	void read(const std::string &str) override;
	auto write() -> std::string override;

	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};

struct CommandCommentLine: ICommandParams
{
	QString line;

	CommandCommentLine() = default;
	CommandCommentLine(QString line);

	int code() override { return 408; }
	void read(const std::string &str) override;
	auto write() -> std::string override;

	int flags() override { return 0; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
