#pragma once
#include "base_command.hpp"

struct CommandSimple: ICommandParams
{
	CommandSimple(int codeVar) { this->codeVar = codeVar;  }

	int codeVar;
	int code() override { return 404; }
	void read(const std::string &str) override { (void)str; };
	auto write() -> std::string override { return "[]"; };

	int flags() override { return 0; };

	void drawImpl(QPainter *painter, bool selected, QRect &rect) override;
};
