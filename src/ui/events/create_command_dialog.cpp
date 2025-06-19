#include "create_command_dialog.hpp"
#include "events/command_text_dialog.hpp"
#include "play_sound_dialog.hpp"
#include "ui_create_command_dialog.h"

CreateCommandDialog::CreateCommandDialog(QModelIndex index, QWidget *parent):
	QDialog(parent), ui(new Ui::CreateCommandDialog)
{
	ui->setupUi(this);

	currentIndex = index;
	connect(ui->showTextButton, &QPushButton::clicked, this, &CreateCommandDialog::openShowTextDialog);
	connect(ui->playSEButton, &QPushButton::clicked, this, &CreateCommandDialog::openPlaySEDialog);
}

CreateCommandDialog::~CreateCommandDialog()
{
	delete dialog;
	delete ui;
}

std::list<Command> CreateCommandDialog::resultCommands()
{
	return dialog ? dialog->resultCommands() : std::list<Command> {};
}

void CreateCommandDialog::openShowTextDialog()
{
	dialog = new CommandTextDialog(false, { currentIndex }, this);
	if (dialog->exec()) accept();
}

void CreateCommandDialog::openPlaySEDialog()
{
	dialog = new PlaySoundDialog(CommandSound::SE, false, currentIndex, this);
	if (dialog->exec()) accept();
}
