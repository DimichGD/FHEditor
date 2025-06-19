#pragma once
#include "base_command.hpp"
#include "sound.hpp"

struct CommandSound: ICommandParams
{
	enum Type
	{
		BGM = 241, BGS = 245, ME = 249, SE = 250,
	};

	Sound sound;
	Type type;

	CommandSound(Type type);
	CommandSound(Type type, Sound sound);

	void read(const std::string &parameters) override;
	std::string write() override;

	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
