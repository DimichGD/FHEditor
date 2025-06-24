#include "wait_dialog.hpp"
#include "command_230.hpp"
#include "ui_wait_dialog.h"

CommandWaitDialog::CommandWaitDialog(bool editing, QModelIndex index, QWidget *parent)
	: CommandDialog(parent), ui(new Ui::WaitDialog)
{
	ui->setupUi(this);

	Command::Iterator command = Command::iteratorFromIndex(index);
	indent = command->indent;

	if (editing)
	{
		auto params = command->parameters.staticCast<Command_230>();
		ui->spinBox->setValue(params->frames);
	}
}

CommandWaitDialog::~CommandWaitDialog()
{
	delete ui;
}

std::list<Command> CommandWaitDialog::resultCommands()
{
	std::list<Command> resultList;

	auto rootParams = CommandFactory::createCommand<Command_230>(ui->spinBox->value());
	resultList.push_back({ CommandFactory::WAIT, indent, rootParams });

	return resultList;
}
