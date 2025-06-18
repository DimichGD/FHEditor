#pragma once
#include "base_command.hpp"
#include "sound.hpp"

struct Command_250: ICommandParams
{
	Sound sound;

	Command_250() = default;
	Command_250(Sound sound);

	void read(const std::string &parameters) override;
	std::string write() override;

	bool canAdd() override { return true; }
	bool canEdit() override { return true; }
	bool canDelete() override { return true; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
