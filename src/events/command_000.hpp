#pragma once
#include "base_command.hpp"

struct Command_000: ICommandParams
{
	Command_000() = default;

	int code() override { return 000; }
	void read(const std::string &str) override { (void)str; };
	auto write() -> std::string override { return "[]"; };

	int flags() override { return CAN_ADD; };

	/*bool canAdd() override { return true; }
	bool canEdit() override { return false; }
	bool canDelete() override { return false; }*/

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
