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

	QString backgroundToString();
	QString windowPositionToString();
	QString faceToString();

	int code() override { return 101; }
	void read(const std::string &parameters) override;
	auto write() -> std::string override;

	bool canAdd() override { return true; }
	bool canEdit() override { return true; }
	bool canDelete() override { return true; }

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
