#include "command_text_dialog.hpp"
#include "icon_picker_dialog.hpp"
#include "images.hpp"
#include "command_101.hpp"
#include "command_line.hpp"
#include "command_factory.hpp"
#include "ui_command_text_dialog.h"

CommandTextDialog::CommandTextDialog(bool editing, QList<QModelIndex> indices, QWidget *parent):
	CommandDialog(parent), ui(new Ui::CommandTextDialog)
{
	ui->setupUi(this);

	Command::Iterator command = Command::iteratorFromIndex(indices[0]);
	indent = command->indent;

	if (editing)
	{
		auto params = static_cast<Command_101_Params *>(command->parameters.get());
		ui->backgroundComboBox->setCurrentIndex(params->background);
		ui->windowPositionComboBox->setCurrentIndex(params->windowPosition);

		for (int i = 1; i < indices.size(); i++)
		{
			std::advance(command, 1);
			auto params = static_cast<CommandLine *>(command->parameters.get());
			ui->messageLinesEdit->appendPlainText(params->line);
		}

		if (!params->faceName.isEmpty())
		{
			ui->faceLabel->setIconMode(ClickableLabel::Mode::FACES,
							Images::Get()->face(params->faceName));
			ui->faceLabel->setIconIndex(params->faceIndex);

			faceName = params->faceName;
			faceIndex = params->faceIndex;
		}
	}

	connect(ui->faceLabel, &ClickableLabel::doubleClicked, this, &CommandTextDialog::openIconPickerDialog);
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
	auto rootParams = CommandFactory::createCommand<Command_101_Params>(faceName, faceIndex, backgroundIndex, windowPositionIndex);
	resultList.push_back({ CommandFactory::TEXT, indent, rootParams });

	QStringList lines = ui->messageLinesEdit->toPlainText().split('\n');
	for (auto &line: lines)
	{
		auto lineParams = CommandFactory::createCommand<CommandLine>(CommandFactory::TEXT_LINE, line);
		resultList.push_back({ CommandFactory::TEXT_LINE, indent, lineParams });
	}

	return resultList;
}

void CommandTextDialog::openIconPickerDialog()
{
	IconPickerDialog dialog(this, PickerType::FACE, faceName, faceIndex);
	if (dialog.exec())
	{
		ui->faceLabel->setIconMode(ClickableLabel::FACES, Images::Get()->face(dialog.name()));
		ui->faceLabel->setIconIndex(dialog.index());

		faceName = dialog.name();
		faceIndex = dialog.index();
	}
}
