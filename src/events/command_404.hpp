#pragma once
#include "base_command.hpp"

struct Command_404: ICommandParams
{
	Command_404() = default;

	int code() override { return 404; }
	void read(const std::string &str) override { (void)str; };
	auto write() -> std::string override { return "[]"; };

	bool canAdd() override { return false; }
	bool canEdit() override { return false; }
	bool canDelete() override { return false; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
