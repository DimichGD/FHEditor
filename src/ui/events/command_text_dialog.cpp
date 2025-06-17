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
		//auto params = command->parameters.staticCast<Command_101>();
		//ui->backgroundComboBox->setCurrentIndex(params->background);
		//ui->windowPositionComboBox->setCurrentIndex(params->windowPosition);

		auto params = std::get<Command_101_Params>(command->parameters);
		ui->backgroundComboBox->setCurrentIndex(std::get<2>(params));
		ui->windowPositionComboBox->setCurrentIndex(std::get<3>(params));

		for (int i = 1; i < indices.size(); i++)
		{
			std::advance(command, 1);
			if (command->code != CommandFactory::LINE)
			{
				qDebug() << "CommandTextDialog error. Expected LINE";
				continue;
			}

			//auto params = command->parameters.staticCast<Command_401>();
			//ui->messageLinesEdit->appendPlainText(params->line);
			auto params = std::get<Command_401_Params>(command->parameters);
			ui->messageLinesEdit->appendPlainText(std::get<0>(params));
		}

		QString &faceName = std::get<0>(params);
		//if (!params->faceName.empty())
		if (!faceName.isEmpty())
		{
			/*ui->faceLabel->setIconMode(ClickableLabel::Mode::FACES,
							Images::Get()->face(QString::fromStdString(params->faceName)));
			ui->faceLabel->setIconIndex(params->faceIndex);*/
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
	//auto rootParams = CommandFactory::createCommand<Command_101>("", 0, backgroundIndex, windowPositionIndex);
	QString emptyString {};
	int emptyInt = 0;
	Command_101_Params rootParams = std::tie(emptyString, emptyInt, backgroundIndex, windowPositionIndex);
	resultList.push_back({ CommandFactory::TEXT, indent, rootParams });

	QStringList lines = ui->messageLinesEdit->toPlainText().split('\n');
	for (auto &line: lines)
	{
		//auto lineParams = CommandFactory::createCommand<Command_401>(line);
		Command_401_Params lineParams = std::tie(line);
		resultList.push_back({ CommandFactory::LINE, indent, lineParams });
	}

	return resultList;
}
