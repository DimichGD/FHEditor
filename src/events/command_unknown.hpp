#pragma once
#include "base_command.hpp"

struct Command_Unknown: ICommandParams
{
	Command_Unknown(int codeId);

	int codeId;
	std::string parameters;

	int code() override { return codeId; }
	void read(const std::string &str) override;
	std::string write() override;

	bool canAdd() override { return false; }
	bool canEdit() override { return false; }
	bool canDelete() override { return false; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
