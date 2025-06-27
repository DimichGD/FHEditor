#pragma once
#include "base_command.hpp"

struct Command_101_Params: ICommandParams
{
	QString faceName;
	int faceIndex;
	int background;
	int windowPosition;

	Command_101_Params() = default;
	Command_101_Params(QString faceName, int faceIndex, int background, int windowPosition);

	int code() override { return 101; }
	int flags() override { return CAN_ADD | CAN_EDIT | CAN_DELETE; };

	void prepare(const QFontMetrics &metrics) override;
	void read(JsonValue &parameters) override;
	auto write() -> std::string override;
};
