#pragma once
#include "base_command.hpp"

struct CommandSimple: ICommandParams
{
	CommandSimple(int codeVar) { this->codeVar = codeVar;  }

	int codeVar;
	int code() override { return codeVar; }
	void read(JsonValue &parameters) override { (void)parameters; }
	auto write() -> std::string override { return "[]"; };

	int flags() override;

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
