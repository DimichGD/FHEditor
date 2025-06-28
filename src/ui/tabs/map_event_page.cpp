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

	mapper = new DataMapper(model, this);
	mapper->add(ui->actorCheckBox, Page::COND_ACTOR_VALID);
	mapper->add(ui->itemCheckBox, Page::COND_ITEM_VALID);
	mapper->add(ui->itemButton, Page::COND_ITEM_ID);
	mapper->add(ui->selfSwitchCheckBox, Page::COND_SELF_SWITCH_VALID);
	mapper->add(ui->selfSwitchComboBox, Page::COND_SELF_SWITCH_CHAR);
	mapper->add(ui->switch1CheckBox, Page::COND_SWITCH_1_VALID);
	mapper->add(ui->switch1Button, Page::COND_SWITCH_1_ID);
	mapper->add(ui->switch2CheckBox, Page::COND_SWITCH_2_VALID);
	mapper->add(ui->switch2Button, Page::COND_SWITCH_2_ID);
	mapper->add(ui->variableCheckBox, Page::COND_VARIABLE_VALID);
	mapper->add(ui->variableButton, Page::COND_VARIABLE_ID);
	mapper->add(ui->directionFixCheckBox, Page::DIRECTION_FIX);
	mapper->add(ui->movementFreqComboBox, Page::MOVE_FREQ);
	mapper->add(ui->movementSpeedComboBox, Page::MOVE_SPEED);
	mapper->add(ui->movementTypeComboBox, Page::MOVE_TYPE);
	mapper->add(ui->priorityComboBox, Page::PRIORITY_TYPE);
	mapper->add(ui->steppingCheckBox, Page::STEP_ANIME);
	mapper->add(ui->throughCheckBox, Page::THROUGH);
	mapper->add(ui->triggerComboBox, Page::TRIGGER);
	mapper->add(ui->walkingCheckBox, Page::WALK_ANIME);
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
