#include "map_event_page.hpp"
#include "ui_map_event_page.h"

MapEventPage::MapEventPage(MapEventPagesModel *model, int index, Page *page, QWidget *parent)
	: QWidget(parent), ui(new Ui::MapEventPage)
{
	ui->setupUi(this);

	ui->eventContentList->loadList(&page->list);
	ui->switch1Button->setSource(SimpleChooserDialog::SWITCH);
	ui->switch2Button->setSource(SimpleChooserDialog::SWITCH);
	ui->variableButton->setSource(SimpleChooserDialog::VARIABLE);
	ui->itemButton->setSource(SimpleChooserDialog::ITEM);

	if (!page->image.characterName.isEmpty())
		if (page->image.tileId == 0)
			ui->imageLabel->setIconImage(page->image);

	mapper = new DataMapper(this);
	mapper->setModel(model);
	mapper->addWidgets({
		{ ui->actorCheckBox, Page::COND_ACTOR_VALID },
		{ ui->itemCheckBox, Page::COND_ITEM_VALID },
		{ ui->itemButton, Page::COND_ITEM_ID },
		{ ui->selfSwitchCheckBox, Page::COND_SELF_SWITCH_VALID },
		{ ui->selfSwitchComboBox, Page::COND_SELF_SWITCH_CHAR },
		{ ui->switch1CheckBox, Page::COND_SWITCH_1_VALID },
		{ ui->switch1Button, Page::COND_SWITCH_1_ID },
		{ ui->switch2CheckBox, Page::COND_SWITCH_2_VALID },
		{ ui->switch2Button, Page::COND_SWITCH_2_ID },
		{ ui->variableCheckBox, Page::COND_VARIABLE_VALID },
		{ ui->variableButton, Page::COND_VARIABLE_ID },
		{ ui->directionFixCheckBox, Page::DIRECTION_FIX },
		{ ui->movementFreqComboBox, Page::MOVE_FREQ },
		{ ui->movementSpeedComboBox, Page::MOVE_SPEED },
		{ ui->movementTypeComboBox, Page::MOVE_TYPE },
		{ ui->priorityComboBox, Page::PRIORITY_TYPE },
		{ ui->steppingCheckBox, Page::STEP_ANIME },
		{ ui->throughCheckBox, Page::THROUGH },
		{ ui->triggerComboBox, Page::TRIGGER },
		{ ui->walkingCheckBox, Page::WALK_ANIME },
	});
	mapper->setCurrentIndex(index);

	ui->selfSwitchComboBox->setEnabled(ui->selfSwitchCheckBox->isChecked());
	ui->switch1Button->setEnabled(ui->switch1CheckBox->isChecked());
	ui->switch2Button->setEnabled(ui->switch2CheckBox->isChecked());
	ui->variableButton->setEnabled(ui->variableCheckBox->isChecked());
	ui->variableSpinBox->setEnabled(ui->variableCheckBox->isChecked());
	ui->itemButton->setEnabled(ui->itemCheckBox->isChecked());
	ui->actorButton->setEnabled(ui->actorCheckBox->isChecked());

	connectCheckBoxToWidget(ui->selfSwitchCheckBox, ui->selfSwitchComboBox);
	connectCheckBoxToWidget(ui->switch1CheckBox, ui->switch1Button);
	connectCheckBoxToWidget(ui->switch2CheckBox, ui->switch2Button);
	connectCheckBoxToWidget(ui->variableCheckBox, ui->variableButton);
	connectCheckBoxToWidget(ui->variableCheckBox, ui->variableSpinBox);
	connectCheckBoxToWidget(ui->itemCheckBox, ui->itemButton);
	connectCheckBoxToWidget(ui->actorCheckBox, ui->actorButton);
}

MapEventPage::~MapEventPage()
{
	delete ui;
}

void MapEventPage::connectCheckBoxToWidget(QCheckBox *checkBox, QWidget *widget)
{
	connect(checkBox, &QCheckBox::stateChanged, this,
			[widget](int state)
			{ widget->setEnabled(state == Qt::Checked); });
}

/*void MapEventPage::connectCheckBoxToWidget(QCheckBox *checkBox, QList<QWidget *> widgets)
{
	connect(checkBox, &QCheckBox::stateChanged, this,
			[&widgets](int state)
			{
				for (auto &widget: widgets)
					widget->setEnabled(state == Qt::Checked);
			});
}*/
