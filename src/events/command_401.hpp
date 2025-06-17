#pragma once
#include "base_command.hpp"

struct Command_401: ICommand
{
	QString line;

	Command_401() = default;
	Command_401(QString line);

	int code() override { return 401; }
	void read(const std::string &str) override;
	auto write() -> std::string override;

	bool canAdd() override { return false; }
	bool canEdit() override { return false; }
	bool canDelete() override { return false; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
