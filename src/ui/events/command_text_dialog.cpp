#include "command_text_dialog.hpp"
#include "images.hpp"
#include "command_101.hpp"
#include "command_401.hpp"
#include "command_factory.hpp"
#include "ui_command_text_dialog.h"

CommandTextDialog::CommandTextDialog(bool editing, QList<QModelIndex> indices, QWidget *parent):
	CommandDialog(parent), ui(new Ui::CommandTextDialog)
{
	ui->setupUi(this);

	Command::It command = indices[0].data(Qt::UserRole + 1).value<Command::It>();
	indent = command->indent;

	if (editing)
	{
		auto params = command->parameters.staticCast<Command_101_Params>();
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

			auto params = command->parameters.staticCast<Command_401_Params>();
			ui->messageLinesEdit->appendPlainText(params->line);
		}

		if (!params->faceName.isEmpty())
		{
			ui->faceLabel->setIconMode(ClickableLabel::Mode::FACES,
							Images::Get()->face(params->faceName));
			ui->faceLabel->setIconIndex(params->faceIndex);
		}
	}
}

CommandTextDialog::~CommandTextDialog()
{
	delete ui;
}

std::list<Command> CommandTextDialog::resultCommands()
{
	std::list<Command> resultList;

	int backgroundIndex = ui->backgroundComboBox->currentIndex();
	int windowPositionIndex = ui->windowPositionComboBox->currentIndex();
	auto rootParams = CommandFactory::createCommand<Command_101_Params>("", 0, backgroundIndex, windowPositionIndex);
	resultList.push_back({ CommandFactory::TEXT, indent, rootParams });

	QStringList lines = ui->messageLinesEdit->toPlainText().split('\n');
	for (auto &line: lines)
	{
		auto lineParams = CommandFactory::createCommand<Command_401_Params>(line);
		resultList.push_back({ CommandFactory::LINE, indent, lineParams });
	}

	return resultList;
}
