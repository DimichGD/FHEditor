#pragma once
#include "base_command.hpp"

struct Command_404: ICommand
{
	Command_404() = default;

	int code() override { return 404; }
	void read(const std::string &str) override { (void)str; };
	auto write() -> std::string override { return "[]"; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
