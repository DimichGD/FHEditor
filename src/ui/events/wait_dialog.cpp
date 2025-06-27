#include "wait_dialog.hpp"
#include "command_wait.hpp"
#include "command_factory.hpp"
#include "ui_wait_dialog.h"
#include <QModelIndex>

CommandWaitDialog::CommandWaitDialog(bool editing, QModelIndex index, QWidget *parent)
	: CommandDialog(parent), ui(new Ui::WaitDialog)
{
	ui->setupUi(this);

	Command::Iterator command = Command::iteratorFromIndex(index);
	indent = command->indent;

	if (editing)
	{
		auto params = static_cast<CommandWait *>(command->parameters.get());
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

	auto rootParams = CommandFactory::createCommand<CommandWait>(ui->spinBox->value());
	resultList.emplace_back(CommandFactory::WAIT, indent, rootParams);

	return resultList;
}
