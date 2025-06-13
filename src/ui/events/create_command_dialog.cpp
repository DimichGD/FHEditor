#include "create_command_dialog.hpp"
#include "events/command_text_dialog.hpp"
#include "ui_create_command_dialog.h"

//#include <QPushButton>

CreateCommandDialog::CreateCommandDialog(QModelIndex index, QWidget *parent):
	QDialog(parent), ui(new Ui::CreateCommandDialog)
{
	ui->setupUi(this);

	currentIndex = index;
	connect(ui->showTextButton, &QPushButton::clicked, this, &CreateCommandDialog::openShowTextDialog);
}

CreateCommandDialog::~CreateCommandDialog()
{
	delete ui;
}

void CreateCommandDialog::openShowTextDialog()
{
	CommandTextDialog dialog(false, { currentIndex }, this);
	if (dialog.exec()) accept();
}
