#include "conditional_branch_dialog.hpp"
#include "command_111.hpp"
#include "ui_conditional_branch_dialog.h"
#include <QRegularExpression>

ConditionalBranchDialog::ConditionalBranchDialog(bool editing, QList<QModelIndex> indices, QWidget *parent) :
	CommandDialog(parent), ui(new Ui::ConditionalBranchDialog)
{
	ui->setupUi(this);

	Command::Iterator rootCommand = Command::iteratorFromIndex(indices[0]);
	indent = rootCommand->indent;

	ui->mainRadioGroup->setId(ui->switchRadioButton, 0);
	ui->mainRadioGroup->setId(ui->variableRadioButton, 1);
	ui->mainRadioGroup->setId(ui->selfSwitchRadionButton, 2);
	ui->mainRadioGroup->setId(ui->timerRadioButton, 3);
	ui->mainRadioGroup->setId(ui->actorRadioButton, 4);
	ui->mainRadioGroup->setId(ui->enemyRadioButton, 5);
	ui->mainRadioGroup->setId(ui->characterRadioButton, 6);
	ui->mainRadioGroup->setId(ui->vehicleRadioButton, 7);
	ui->mainRadioGroup->setId(ui->goldRadioButton, 8);
	ui->mainRadioGroup->setId(ui->itemRadioButton, 9);
	ui->mainRadioGroup->setId(ui->weaponRadioButton, 10);
	ui->mainRadioGroup->setId(ui->armorRadioButton, 11);
	ui->mainRadioGroup->setId(ui->buttonRadioButton, 12);
	ui->mainRadioGroup->setId(ui->scriptRadioButton, 13);
	ui->variableRadioGroup->setId(ui->variableConstantRadioButton, 0);
	ui->variableRadioGroup->setId(ui->variableVariableRadionButton, 1);
	ui->actorRadioGroup->setId(ui->actorInPartyRadioButton, 0);
	ui->actorRadioGroup->setId(ui->actorNameRadioButton, 1);
	ui->actorRadioGroup->setId(ui->actorClassRadioButton, 2);
	ui->actorRadioGroup->setId(ui->actorSkillRadioButton, 3);
	ui->actorRadioGroup->setId(ui->actorWeaponRadioButton, 4);
	ui->actorRadioGroup->setId(ui->actorArmorRadioButton, 5);
	ui->actorRadioGroup->setId(ui->actorStateRadioButton, 6);
	ui->enemyRadioGroup->setId(ui->enemyAppearedRadioButton, 0);
	ui->enemyRadioGroup->setId(ui->enemyStateRadioButton, 1);

	ui->switchButton->setSource(SimpleChooserDialog::SWITCH);
	ui->variableButton->setSource(SimpleChooserDialog::VARIABLE);
	ui->variableVariableButton->setSource(SimpleChooserDialog::VARIABLE);
	ui->actorButton->setSource(SimpleChooserDialog::ACTOR);
	ui->actorClassButton->setSource(SimpleChooserDialog::CLASS);
	ui->actorSkillButton->setSource(SimpleChooserDialog::SKILL);
	ui->actorWeaponButton->setSource(SimpleChooserDialog::WEAPON);
	ui->actorArmorButton->setSource(SimpleChooserDialog::ARMOR);
	ui->actorStateButton->setSource(SimpleChooserDialog::STATE);
	ui->enemyStateButton->setSource(SimpleChooserDialog::STATE);
	ui->itemButton->setSource(SimpleChooserDialog::ITEM);
	ui->weaponButton->setSource(SimpleChooserDialog::WEAPON);
	ui->armorButton->setSource(SimpleChooserDialog::ARMOR);

	// TODO: set defaut id to 1 in button constructor?
	ui->switchButton->setProperty("id", 1);
	ui->variableButton->setProperty("id", 1);
	ui->variableVariableButton->setProperty("id", 1);
	ui->actorButton->setProperty("id", 1);
	ui->actorClassButton->setProperty("id", 1);
	ui->actorSkillButton->setProperty("id", 1);
	ui->actorWeaponButton->setProperty("id", 1);
	ui->actorArmorButton->setProperty("id", 1);
	ui->actorStateButton->setProperty("id", 1);
	ui->enemyStateButton->setProperty("id", 1);
	ui->itemButton->setProperty("id", 1);
	ui->weaponButton->setProperty("id", 1);
	ui->armorButton->setProperty("id", 1);

	connect(ui->mainRadioGroup, &QButtonGroup::idToggled, this, &ConditionalBranchDialog::radioButtonToggled);

	if (editing)
	{
		Command::Iterator elseCommand;
		Command::Iterator endCommand = Command::iteratorFromIndex(indices.last());

		for (Command::Iterator it = rootCommand; it != endCommand; ++it)
		{
			if (it->code == 411)
			{
				ui->elseBranchCheckBox->setCheckState(Qt::Checked);
				elseCommand = it;
			}
		}

		if (ui->elseBranchCheckBox->isChecked())
		{
			bodyList = { std::next(rootCommand), elseCommand };
			elseList = { std::next(elseCommand), endCommand };
		}
		else
		{
			bodyList = { std::next(rootCommand), endCommand };
		}

		JsonValue &value = rootCommand->parameters.staticCast<Command_111>()->condData;
		int index = value[0].toInt();
		ui->mainRadioGroup->button(index)->toggle();
		fillWidgets(value);

		if (index >= 0 && index <= 3)
			ui->tabWidget->setCurrentIndex(0);

		else if (index == 4)
			ui->tabWidget->setCurrentIndex(1);

		else if (index >= 5 && index <= 7)
			ui->tabWidget->setCurrentIndex(2);

		else
			ui->tabWidget->setCurrentIndex(3);
	}
}

ConditionalBranchDialog::~ConditionalBranchDialog()
{
	delete ui;
}

std::list<Command> ConditionalBranchDialog::resultCommands()
{
	std::list<Command> commands;
	JsonValue::array_t condData;

	int index = ui->mainRadioGroup->checkedId();
	condData.push_back({ double(index) });
	switch (index)
	{
		case 0:
			condData.push_back({ ui->switchButton->property("id").toDouble() });
			condData.push_back({ double(ui->switchComboBox->currentIndex()) });
			break;

		case 1:
			condData.push_back({ ui->variableButton->property("id").toDouble() });
			condData.push_back({ double(ui->variableRadioGroup->checkedId()) });
			if (ui->variableRadioGroup->checkedId() == 0)
				condData.push_back({ double(ui->variableConstantSpinBox->value()) });
			else
				condData.push_back({ ui->variableVariableButton->property("id").toDouble() });
			condData.push_back({ double(ui->variableSignComboBox->currentIndex()) });
			break;

		case 2:
			condData.push_back({ ui->selfSwitchComboBox->currentText().toStdString() });
			condData.push_back({ double(ui->selfSwitchToggleComboBox->currentIndex()) });
			break;

		case 3:
			condData.push_back({ double(ui->timerSecSpinBox->value() + ui->timerMinSpinBox->value() * 60) });
			condData.push_back({ double(ui->timerSignComboBox->currentIndex()) });
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		case 9:
			break;

		case 10:
			break;

		case 11:
			break;

		case 12:
			break;

		case 13:
			break;
	}

	commands.push_back({ CommandFactory::IF, indent, CommandFactory::createCommand<Command_111>(JsonValue { condData }) });

	if (!bodyList.empty())
	{
		if (!elseList.empty())
		{
			commands.insert(commands.end(), bodyList.begin(), bodyList.end());
			commands.push_back({ CommandFactory::ELSE, indent, CommandFactory::createCommand2(411) });
			commands.insert(commands.end(), elseList.begin(), elseList.end());
		}
		else
		{
			commands.insert(commands.end(), bodyList.begin(), bodyList.end());
		}
	}
	else
	{
		commands.push_back(Command::makeZeroCommand(indent + 1));
		if (ui->elseBranchCheckBox->isChecked())
		{
			commands.push_back({ CommandFactory::ELSE, indent, CommandFactory::createCommand2(411) });
			commands.push_back(Command::makeZeroCommand(indent + 1));
		}
	}

	commands.push_back({ CommandFactory::END_IF, indent, CommandFactory::createCommand2(412) });

	return commands;
}

void ConditionalBranchDialog::setWidgetsVisible(QString prefix, bool toggled)
{
	QRegularExpression re(QString("^%1").arg(prefix));
	for (auto &widget: ui->tabWidget->findChildren<QWidget *>(re))
		if (widget->objectName() != prefix + "RadioButton")
			widget->setEnabled(toggled);
}

void ConditionalBranchDialog::radioButtonToggled(int index, bool toggled)
{
	QStringList prefixList = {
		"switch",
		"variable",
		"selfSwitch",
		"timer",
		"actor",
		"enemy",
		"character",
		"vehicle",
		"gold",
		"item",
		"weapon",
		"armor",
		"button",
		"script",
	};

	setWidgetsVisible(prefixList[index], toggled);
}

void ConditionalBranchDialog::fillWidgets(JsonValue &value)
{
	int index = value[0].toInt();
	switch (index)
	{
		case 0:
			ui->switchButton->setProperty("id", value[1].toInt());
			ui->switchComboBox->setCurrentIndex(value[2].toInt());
			break;

		case 1:
			ui->variableButton->setProperty("id", value[1].toInt());
			ui->variableSignComboBox->setCurrentIndex(value[4].toInt());
			if (value[2].toInt() == 0)
			{
				ui->variableConstantRadioButton->setChecked(true);
				ui->variableConstantSpinBox->setValue(value[3].toInt());
			}
			else
			{
				ui->variableVariableRadionButton->setChecked(true);
				ui->variableVariableButton->setProperty("id", value[3].toInt());
			}
			break;

		case 2:
			ui->selfSwitchComboBox->setCurrentIndex(value[1].toQString()[0].toLatin1() - 65);
			ui->selfSwitchToggleComboBox->setCurrentIndex(value[2].toInt());
			break;

		case 3:
			ui->timerSignComboBox->setCurrentIndex(value[2].toInt());
			ui->timerMinSpinBox->setValue(value[1].toInt() / 60);
			ui->timerSecSpinBox->setValue(value[1].toInt() % 60);
			break;

		case 4:
			break;

		case 5:
			break;

		case 6:
			break;

		case 7:
			break;

		case 8:
			break;

		case 9:
			break;

		case 10:
			break;

		case 11:
			break;

		case 12:
			break;

		case 13:
			break;
	}
}
