#pragma once
#include "base_command.hpp"

struct Command_102: ICommandParams
{
	std::vector<std::string> choices;
	int value_0; // cancel (-2: add Cancel barnch, -1: Disallow, 0..5: #1-#6)
	int value_1; // default (0: None, 0..5: #1-#6)
	int value_2; // windowPosition
	int value_3; // background

	Command_102() = default;
	Command_102(std::vector<std::string> choices, int value_0,
				int value_1, int value_2, int value_3);

	QString backgroundToString();
	QString windowPositionToString();

	int code() override { return 102; }
	void read(const std::string &parameters) override;
	auto write() -> std::string override;

	bool canAdd() override { return true; }
	bool canEdit() override { return true; }
	bool canDelete() override { return true; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
