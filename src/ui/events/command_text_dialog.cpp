#include "command_text_dialog.hpp"
#include "images.hpp"
#include "command_101.hpp"
#include "command_401.hpp"
#include "command_factory.hpp"
#include "ui_command_text_dialog.h"

CommandTextDialog::CommandTextDialog(bool editing, QList<QModelIndex> indices, QWidget *parent):
	QDialog(parent), ui(new Ui::CommandTextDialog)
{
	ui->setupUi(this);
	this->editing = editing;

	selectionSize = indices.size();
	event = indices[0].data(Qt::UserRole + 0).value<Event *>();
	Command::It command = indices[0].data(Qt::UserRole + 1).value<Command::It>();
	rootCommand = command;
	if (command->code == CommandFactory::TEXT) // editing
	{
		auto params = command->parameters.staticCast<Command_101>();
		ui->backgroundComboBox->setCurrentIndex(params->background);
		ui->windowPositionComboBox->setCurrentIndex(params->windowPosition);

		for (int i = 1; i < indices.size(); i++)
		{
			std::advance(command, 1);
			if (command->code != CommandFactory::LINE)
			{
				qDebug() << "CommandTextDialog error. Expected LINE";
				continue;
			}

			auto params = command->parameters.staticCast<Command_401>();
			ui->messageLinesEdit->appendPlainText(params->line);
		}

		if (!params->faceName.empty())
		{
			ui->faceLabel->setIconMode(ClickableLabel::Mode::FACES,
							Images::Get()->face(QString::fromStdString(params->faceName)));
			ui->faceLabel->setIconIndex(params->faceIndex);
		}
	}

	connect(this, &QDialog::accepted, this, &CommandTextDialog::makeChanges);
}

CommandTextDialog::~CommandTextDialog()
{
	delete ui;
}

void CommandTextDialog::makeChanges()
{
	Command::It command = rootCommand;

	if (editing)
	{
		for (int i = 0; i < selectionSize; i++)
			command = event->list.erase(command);
	}

	int indent = rootCommand->indent; // FIXME: read from deleted iterator?
	command = event->list.insert(command, { CommandFactory::TEXT, indent, {} });
	int backgoundIndex = ui->backgroundComboBox->currentIndex();
	int windowPositionIndex = ui->windowPositionComboBox->currentIndex();
	command->parameters = CommandFactory::createCommand<Command_101>("", 0, backgoundIndex, windowPositionIndex);

	std::advance(command, 1);
	QStringList lines = ui->messageLinesEdit->toPlainText().split('\n');
	for (auto &line: lines)
	{
		auto newCommand = event->list.insert(command, { CommandFactory::LINE, indent, {} });
		newCommand->parameters = CommandFactory::createCommand<Command_401>(line);
	}
}
