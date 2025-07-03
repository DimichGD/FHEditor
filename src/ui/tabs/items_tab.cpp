#include "items_tab.hpp"
#include "change_maximum_dialog.hpp"
//#include "icon_picker_dialog.hpp"
#include "database.hpp"
//#include "iconset.hpp"
#include "images.hpp"
#include "item_effects_model.hpp"
#include "item_effect_dialog.hpp"
#include "data_mapper.hpp"
#include "items_model.hpp"
#include "menu.hpp"
#include "ui_items_tab.h"

ItemsTab::ItemsTab(QWidget *parent): QWidget(parent), ui(new Ui::ItemsTab)
{
	ui->setupUi(this);
	itemEffectsListMenu = createMenu(this,
	{
		ui->actionEffectNew, ui->actionEffectEdit,
		ui->actionEffectGoTo, nullptr, ui->actionEffectDelete
	});

	connect(ui->actionEffectNew, &QAction::triggered, this, &ItemsTab::actionEffectNewTriggered);
	connect(ui->actionEffectEdit, &QAction::triggered, this, &ItemsTab::actionEffectEditTriggered);
	connect(ui->actionEffectDelete, &QAction::triggered, this, &ItemsTab::actionEffectDeleteTriggered);
	connect(ui->actionEffectGoTo, &QAction::triggered, this, &ItemsTab::actionEffectGotToTriggered);

	connect(ui->itemEffectsList, &QTableView::customContextMenuRequested, this, &ItemsTab::contextMenuRequested);
	connect(ui->itemEffectsList, &QTableView::doubleClicked, ui->itemEffectsList, [this](const QModelIndex &) { actionEffectEditTriggered(true); });

	connect(ui->itemsTable, &BaseTable::rowSelected, this, &ItemsTab::itemRowSelected);
	connect(ui->itemNameFilter, &QLineEdit::textChanged, ui->itemsTable, &BaseTable::setFilterText);
	connect(ui->itemDamageTypeComboBox, &QComboBox::currentIndexChanged, this, &ItemsTab::itemDamageTypeChanged);

	connect(ui->itemNewButton, &QPushButton::clicked, this, &ItemsTab::itemNewClicked);
	connect(ui->itemClearButton, &QPushButton::clicked, this, &ItemsTab::itemClearClicked);
	connect(ui->itemResizeButton, &QPushButton::clicked, this, &ItemsTab::itemResizeClicked);

	model = new ItemsModel(this);
	effectsModel = new ItemEffectsModel(model, this);

	mapper = new DataMapper(model, this);
	mapper->add(ui->itemAnimationButton, Item::ANIMATION_ID);
	mapper->add(ui->itemConsumableComboBox, Item::CONSUMABLE);
	mapper->add(ui->itemDamageCriticalHitsComboBox, Item::DAMAGE_CRITICAL);
	mapper->add(ui->itemDamageElementComboBox, Item::DAMAGE_ELEMENT);
	mapper->add(ui->itemDamageFormulaEdit, Item::DAMAGE_FORMULA);
	mapper->add(ui->itemDamageTypeComboBox, Item::DAMAGE_TYPE);
	mapper->add(ui->itemDamageVarianceSpinBox, Item::DAMAGE_VARIANCE);
	mapper->add(ui->itemDescEdit, Item::DESC);
	mapper->add(ui->itemHitTypeComboBox, Item::HIT_TYPE);
	mapper->add(ui->itemIconWidget, Item::ICON_INDEX);
	mapper->add(ui->itemTypeComboBox, Item::ITEM_TYPE);
	mapper->add(ui->itemNameEdit, Item::NAME);
	mapper->add(ui->itemNotes, Item::NOTE);
	mapper->add(ui->itemOccasionComboBox, Item::OCCASION);
	mapper->add(ui->itemPriceSpinBox, Item::PRICE);
	mapper->add(ui->itemRepeatSpinBox, Item::REPEAT);
	mapper->add(ui->itemScopeComboBox, Item::SCOPE);
	mapper->add(ui->itemSpeedSpinBox, Item::SPEED);
	mapper->add(ui->itemSuccessSpinBox, Item::SUCCESS);
	mapper->add(ui->itemTPGainSpinBox, Item::TP_GAIN);

	ui->itemEffectsList->setModel(effectsModel);
	ui->itemsTable->setModel2(model, Item::NAME);
	ui->itemAnimationButton->setSource(SimpleChooserDialog::ANIMATION);

	for (int i = 0; i < Item::COUNT; i++)
		ui->itemsTable->setColumnHidden(i, true);

	ui->itemsTable->setColumnHidden(Item::ID, false);
	ui->itemsTable->setColumnHidden(Item::ICON_INDEX, false);
	ui->itemsTable->setColumnHidden(Item::NAME, false);
	ui->itemsTable->resizeColumnToContents(Item::ID);
	ui->itemsTable->resizeColumnToContents(Item::ICON_INDEX);
	ui->itemsTable->setItemDelegateForColumn(Item::ICON_INDEX, new IconDelegate(Images::Get()->iconSet(), this));
}

ItemsTab::~ItemsTab()
{
	delete ui;
}



void ItemsTab::init()
{
	model->reset();

	ui->itemDamageElementComboBox->clear(); // Normal Attack and None only present in items?
	ui->itemDamageElementComboBox->addItem("Normal Attack"); // -1

	// TODO: make model for this
	std::vector<QString> &elements = Database::Get()->system()->elements;
	for (size_t i = 0; i < elements.size(); i++) // 1..x
		if (!elements[i].isEmpty())
			ui->itemDamageElementComboBox->addItem(elements[i]);
		else
			ui->itemDamageElementComboBox->addItem(QString("#%1").arg(i, 2, 10, QChar('0')));
	ui->itemDamageElementComboBox->setItemText(1, "None");  // 0

	ui->itemsTable->selectRow(0);
}

void ItemsTab::itemRowSelected(int row)
{
	if (!model->item(row))
	{
		effectsModel->setItemIndex(-1);
		mapper->setCurrentIndex(-1);
		enableGroupBoxes(false);
		return;
	}

	if (!ui->generalBox->isEnabled())
		enableGroupBoxes(true);

	mapper->setCurrentIndex(row);
	effectsModel->setItemIndex(row);
}

void ItemsTab::itemDamageTypeChanged(int index)
{
	bool toggle = index != 0;

	ui->itemDamageElementComboBox->setEnabled(toggle);
	ui->itemDamageFormulaEdit->setEnabled(toggle);
	ui->itemDamageVarianceSpinBox->setEnabled(toggle);
	ui->itemDamageCriticalHitsComboBox->setEnabled(toggle);
}


void ItemsTab::contextMenuRequested(const QPoint &pos)
{
	QModelIndex index = ui->itemEffectsList->indexAt(pos);
	bool enabled = index.isValid();

	ui->actionEffectEdit->setEnabled(enabled);
	ui->actionEffectDelete->setEnabled(enabled);

	//bool flag = enabled && index.data(ItemEffectsModel::CODE).toInt() == Effect::COMMON_EVENT;
	bool flag = enabled && effectsModel->effectCode(index.row()) == Effect::COMMON_EVENT;
	ui->actionEffectGoTo->setEnabled(flag);

	itemEffectsListMenu->exec(ui->itemEffectsList->viewport()->mapToGlobal(pos));
}

void ItemsTab::actionEffectNewTriggered(bool)
{
	effectsModel->addEffect();
	ui->itemEffectsList->selectRow(effectsModel->rowCount() - 1);
}

void ItemsTab::actionEffectEditTriggered(bool)
{
	int effectIndex = ui->itemEffectsList->currentIndex().row();
	ItemEffectDialog dialog(*effectsModel->effect(effectIndex), this); // FIXME: why value instead of pointer?
	if (dialog.exec())
	{
		effectsModel->setEffect(effectIndex, dialog.value());
		ui->itemEffectsList->selectRow(effectIndex);
	}
}

void ItemsTab::actionEffectDeleteTriggered(bool)
{
	int effectIndex = ui->itemEffectsList->currentIndex().row();
	effectsModel->removeEffect(effectIndex);
}

void ItemsTab::actionEffectGotToTriggered(bool)
{
	int effectIndex = ui->itemEffectsList->currentIndex().row();
	emit selectCommonEvent(effectsModel->effectCode(effectIndex));
}


void ItemsTab::enableGroupBoxes(bool enabled)
{
	if (!enabled)
		ui->itemIconWidget->setIconIndex(0);

	ui->generalBox->setEnabled(enabled);
	ui->invocationBox->setEnabled(enabled);
	ui->damageBox->setEnabled(enabled);
	ui->effectsBox->setEnabled(enabled);
	ui->notesBox->setEnabled(enabled);
}

void ItemsTab::itemNewClicked()
{
	model->changeCount(model->rowCount() + 1);
	ui->itemsTable->selectRow(ui->itemsTable->rowCount() - 1);
}

void ItemsTab::itemResizeClicked()
{
	ChangeMaximumDialog dialog(model, ui->itemResizeButton);
	if (dialog.exec())
		model->changeCount(dialog.value());
}

void ItemsTab::itemClearClicked()
{
	model->clearRow(ui->itemsTable->selectedRow());
	effectsModel->setItemIndex(-1);
}

