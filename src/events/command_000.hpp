#pragma once
#include "base_command.hpp"

struct Command_000: ICommandParams
{
	Command_000() = default;

	int code() override { return 000; }
	void read(const std::string &str) override { (void)str; };
	void read(const std::vector<glz::json_t> &parameters) override { (void)parameters; };
	auto write() -> std::string override { return "[]"; };

	int flags() override { return CAN_ADD; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
