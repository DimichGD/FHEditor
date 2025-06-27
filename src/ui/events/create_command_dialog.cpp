#include "create_command_dialog.hpp"
#include "command_000.hpp"
#include "command_simple.hpp"
#include "command_factory.hpp"
#include "conditional_branch_dialog.hpp"
#include "events/command_text_dialog.hpp"
#include "play_sound_dialog.hpp"
#include "ui_create_command_dialog.h"
#include "wait_dialog.hpp"

CreateCommandDialog::CreateCommandDialog(QModelIndex index, QWidget *parent):
	QDialog(parent), ui(new Ui::CreateCommandDialog)
{
	ui->setupUi(this);

	currentIndex = index;
	indent = Command::iteratorFromIndex(currentIndex)->indent;

	connect(ui->showTextButton, &QPushButton::clicked, this, &CreateCommandDialog::openShowTextDialog);
	connect(ui->conditionalBranchButton, &QPushButton::clicked, this, &CreateCommandDialog::openConditionalBranchDialog);
	connect(ui->waitButton, &QPushButton::clicked, this, &CreateCommandDialog::openWaitDialog);
	connect(ui->playBGMButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlayBGMDialog);
	connect(ui->playBGSButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlayBGSDialog);
	connect(ui->playMEButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlayMEDialog);
	connect(ui->playSEButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlaySEDialog);
	connect(ui->playSEButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlaySEDialog);
	connect(ui->stopSEButton, &QPushButton::clicked, this, &CreateCommandDialog::makeStopSECommand);
	connect(ui->gatherFollowersButton, &QPushButton::clicked, this, &CreateCommandDialog::makeGatherFollowersCommand);
	connect(ui->loopButton, &QPushButton::clicked, this, &CreateCommandDialog::makeLoopCommand);
	connect(ui->breakLoopButton, &QPushButton::clicked, this, &CreateCommandDialog::makeBreakLoopCommand);
	connect(ui->openSaveButton, &QPushButton::clicked, this, &CreateCommandDialog::makeOpenSaveCommand);
	connect(ui->gameOverButton, &QPushButton::clicked, this, &CreateCommandDialog::makeGameOverCommand);
}

CreateCommandDialog::~CreateCommandDialog()
{
	delete ui;
}

std::list<Command> CreateCommandDialog::resultCommands()
{
	return dialog ? dialog->resultCommands() : std::move(commands);
}

void CreateCommandDialog::openShowTextDialog()
{
	dialog = new CommandTextDialog(false, { currentIndex }, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openConditionalBranchDialog()
{
	dialog = new ConditionalBranchDialog(false, { currentIndex }, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openWaitDialog()
{
	dialog = new CommandWaitDialog(false, currentIndex, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openPlayBGMDialog()
{
	dialog = new PlaySoundDialog(CommandSound::BGM, false, currentIndex, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openPlayBGSDialog()
{
	dialog = new PlaySoundDialog(CommandSound::BGS, false, currentIndex, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openPlayMEDialog()
{
	dialog = new PlaySoundDialog(CommandSound::ME, false, currentIndex, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openPlaySEDialog()
{
	dialog = new PlaySoundDialog(CommandSound::SE, false, currentIndex, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::makeGatherFollowersCommand()
{
	commands.emplace_back(Command { CommandFactory::GATHER_FOLLOWERS, indent,
									CommandFactory::createCommand<CommandSimple>(217) });
	accept();
}

void CreateCommandDialog::makeStopSECommand()
{
	commands.emplace_back(Command { CommandFactory::STOP_SE, indent,
									CommandFactory::createCommand<CommandSimple>(251) });
	accept();
}

void CreateCommandDialog::makeLoopCommand()
{
	commands.emplace_back(Command { CommandFactory::LOOP, indent,
									CommandFactory::createCommand<CommandSimple>(112) });
	commands.emplace_back(Command::makeZeroCommand(indent + 1));
	commands.emplace_back(Command { CommandFactory::REPEAT_LOOP, indent,
									CommandFactory::createCommand<CommandSimple>(413) });
	accept();
}

void CreateCommandDialog::makeBreakLoopCommand()
{
	commands.emplace_back(Command { CommandFactory::BREAK_LOOP, indent,
									CommandFactory::createCommand<CommandSimple>(113) });
	accept();
}

void CreateCommandDialog::makeOpenSaveCommand()
{
	commands.emplace_back(Command { CommandFactory::OPEN_SAVE_SCREEN, indent,
									CommandFactory::createCommand<CommandSimple>(352) });
	accept();
}

void CreateCommandDialog::makeGameOverCommand()
{
	commands.emplace_back(Command { CommandFactory::GAME_OVER, indent,
									CommandFactory::createCommand<CommandSimple>(353) });
	accept();
}
