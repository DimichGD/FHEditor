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

	int code() override { return type; }
	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	std::string write() override;
};
