#include "item_effect_dialog.hpp"
#include "ui_item_effect_dialog.h"

#include <QDataWidgetMapper>
#include <QStandardItemModel>
#include <set>

static std::set<int> needConvert { Effect::RECOVER_HP, Effect::RECOVER_MP,
									Effect::ADD_STATE, Effect::REMOVE_STATE };

void ItemEffectDialog::setModelRow(int index, int code, int dataId, int value1, int value2)
{
	models[index]->setData(models[index]->index(0, 0), code);
	models[index]->setData(models[index]->index(0, 1), dataId);
	models[index]->setData(models[index]->index(0, 2), value1);
	models[index]->setData(models[index]->index(0, 3), value2);
}

int tabIndex(int code)
{
	return code / 10 - 1;
}

int rowIndex(int code)
{
	int tab = tabIndex(code);
	int index = code % 10 - 1;

	if      (tab == 1) index += 3;
	else if (tab == 2) index += 5;
	else if (tab == 3) index += 9;

	return index;
}

ItemEffectDialog::ItemEffectDialog(Effect effect, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ItemEffectDialog)
{
	ui->setupUi(this);
	ui->addStateButton->setSource(SimpleChooserDialog::STATE);
	ui->removeStateButton->setSource(SimpleChooserDialog::STATE);
	ui->learnSkillButton->setSource(SimpleChooserDialog::SKILL);
	ui->commonEventButton->setSource(SimpleChooserDialog::COMMON_EVENT);

	ui->radioGroup->setId(ui->recoverHPRadioButton, Effect::RECOVER_HP);
	ui->radioGroup->setId(ui->recoverMPRadioButton, Effect::RECOVER_MP);
	ui->radioGroup->setId(ui->gainTPRadioButton, Effect::GAIN_TP);
	ui->radioGroup->setId(ui->addStateRadioButton, Effect::ADD_STATE);
	ui->radioGroup->setId(ui->removeStateRadioButton, Effect::REMOVE_STATE);
	ui->radioGroup->setId(ui->addBuffRadioButton, Effect::ADD_BUFF);
	ui->radioGroup->setId(ui->addDebuffRadioButton, Effect::ADD_DEBUFF);
	ui->radioGroup->setId(ui->removeBuffRadioButton, Effect::REMOVE_BUFF);
	ui->radioGroup->setId(ui->removeDebuffRadioButton, Effect::REMOVE_DEBUFF);
	ui->radioGroup->setId(ui->specialEffectRadioButton, Effect::SPECIAL);
	ui->radioGroup->setId(ui->growRadioButton, Effect::GROW);
	ui->radioGroup->setId(ui->learnSkillRadioButton, Effect::LEARN_SKILL);
	ui->radioGroup->setId(ui->commonEventRadioButton, Effect::COMMON_EVENT);
	ui->radioGroup->button(effect.code)->setChecked(true);
	radioButtonToggled(ui->radioGroup->checkedId(), true);

	ui->tabWidget->setCurrentIndex(tabIndex(effect.code));

	for (int i = 0; i < 13; i++)
	{
		models[i] = new QStandardItemModel(1, 4, this);
		mappers[i] = new QDataWidgetMapper(this);
		mappers[i]->setModel(models[i]);
	}

	setModelRow(0, Effect::RECOVER_HP, 0, 100, 0);
	setModelRow(1, Effect::RECOVER_MP, 0, 100, 0);
	setModelRow(2, Effect::GAIN_TP, 0, 0, 0);
	setModelRow(3, Effect::ADD_STATE, 1, 100, 0);
	setModelRow(4, Effect::REMOVE_STATE, 1, 100, 0);
	setModelRow(5, Effect::ADD_BUFF, 0, 5, 0);
	setModelRow(6, Effect::ADD_DEBUFF, 0, 5, 0);
	setModelRow(7, Effect::REMOVE_BUFF, 0, 0, 0);
	setModelRow(8, Effect::REMOVE_DEBUFF, 0, 0, 0);
	setModelRow(9, Effect::SPECIAL, 0, 0, 0);
	setModelRow(10, Effect::GROW, 0, 1, 0);
	setModelRow(11, Effect::LEARN_SKILL, 1, 0, 0);
	setModelRow(12, Effect::COMMON_EVENT, 0, 0, 0);

	if (needConvert.contains(effect.code))
		setModelRow(rowIndex(effect.code),
					effect.code, effect.dataId, effect.value1 * 100, effect.value2);
	else
		setModelRow(rowIndex(effect.code),
					effect.code, effect.dataId, effect.value1, effect.value2);

	//std::set<int> needLookup { Effect::ADD_STATE, Effect::REMOVE_STATE,
	//							Effect::LEARN_SKILL, Effect::COMMON_EVENT };

	mappers[0]->addMapping(ui->recoverHPValue1SpinBox, 2);
	mappers[0]->addMapping(ui->recoverHPValue2SpinBox, 3);
	mappers[1]->addMapping(ui->recoverMPValue1SpinBox, 2);
	mappers[1]->addMapping(ui->recoverMPValue2SpinBox, 3);
	mappers[2]->addMapping(ui->gainTPValueSpinBox, 2);
	mappers[3]->addMapping(ui->addStateButton, 1, "id");
	mappers[3]->addMapping(ui->addStateSpinBox, 2);
	mappers[4]->addMapping(ui->removeStateButton, 1, "id");
	mappers[4]->addMapping(ui->removeStateSpinBox, 2);
	mappers[5]->addMapping(ui->addBuffComboBox, 1, "currentIndex");
	mappers[5]->addMapping(ui->addBuffSpinBox, 2);
	mappers[6]->addMapping(ui->addDebuffComboBox, 1, "currentIndex");
	mappers[6]->addMapping(ui->addDebuffSpinBox, 2);
	mappers[7]->addMapping(ui->removeBuffComboBox, 1, "currentIndex");
	mappers[8]->addMapping(ui->removeDebuffComboBox, 1, "currentIndex");
	mappers[9]->addMapping(ui->specialEffectComboBox, 1, "currentIndex");
	mappers[10]->addMapping(ui->growComboBox, 1, "currentIndex");
	mappers[10]->addMapping(ui->growSpinBox, 2);
	mappers[11]->addMapping(ui->learnSkillButton, 1, "id");
	mappers[12]->addMapping(ui->commonEventButton, 1, "id");

	for (int i = 0; i < 13; i++)
		mappers[i]->toFirst();

	connect(ui->radioGroup, &QButtonGroup::idToggled, this, &ItemEffectDialog::radioButtonToggled);
}

ItemEffectDialog::~ItemEffectDialog()
{
	delete ui;
}

Effect ItemEffectDialog::value()
{
	int code = ui->radioGroup->checkedId();
	QStandardItemModel *model = models[rowIndex(code)];

	Effect effect
	{
		.code = code,
		.dataId = model->data(model->index(0, 1)).toInt(),
		.value1 = float(model->data(model->index(0, 2)).toInt()),
		.value2 = float(model->data(model->index(0, 3)).toInt()),
	};

	if (needConvert.contains(code))
		effect.value1 *= 0.01f;

	return effect;
}

void ItemEffectDialog::radioButtonToggled(int index, bool toggled)
{
	switch (index)
	{
		case Effect::RECOVER_HP:
			ui->recoverHPValue1SpinBox->setEnabled(toggled);
			ui->recoverHPValue2SpinBox->setEnabled(toggled);
			break;

		case Effect::RECOVER_MP:
			ui->recoverMPValue1SpinBox->setEnabled(toggled);
			ui->recoverMPValue2SpinBox->setEnabled(toggled);
			break;

		case Effect::GAIN_TP:
			ui->gainTPValueSpinBox->setEnabled(toggled);
			break;

		case Effect::ADD_STATE:
			ui->addStateButton->setEnabled(toggled);
			ui->addStateSpinBox->setEnabled(toggled);
			break;

		case Effect::REMOVE_STATE:
			ui->removeStateButton->setEnabled(toggled);
			ui->removeStateSpinBox->setEnabled(toggled);
			break;

		case Effect::ADD_BUFF:
			ui->addBuffComboBox->setEnabled(toggled);
			ui->addBuffSpinBox->setEnabled(toggled);
			ui->addBuffLabel->setEnabled(toggled);
			break;

		case Effect::ADD_DEBUFF:
			ui->addDebuffComboBox->setEnabled(toggled);
			ui->addDebuffSpinBox->setEnabled(toggled);
			ui->addDebuffLabel->setEnabled(toggled);
			break;

		case Effect::REMOVE_BUFF:
			ui->removeBuffComboBox->setEnabled(toggled);
			break;

		case Effect::REMOVE_DEBUFF:
			ui->removeDebuffComboBox->setEnabled(toggled);
			break;

		case Effect::SPECIAL:
			ui->specialEffectComboBox->setEnabled(toggled);
			break;

		case Effect::GROW:
			ui->growComboBox->setEnabled(toggled);
			ui->growSpinBox->setEnabled(toggled);
			break;

		case Effect::LEARN_SKILL:
			ui->learnSkillButton->setEnabled(toggled);
			break;

		case Effect::COMMON_EVENT:
			ui->commonEventButton->setEnabled(toggled);
			break;
	}
}
