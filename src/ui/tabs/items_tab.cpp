#include "items_tab.hpp"
#include "change_maximum_dialog.hpp"
#include "icon_picker_dialog.hpp"
#include "database.hpp"
//#include "iconset.hpp"
#include "images.hpp"
#include "item_effects_model.hpp"
#include "item_effect_dialog.hpp"
#include "data_mapper.hpp"
#include "items_model.hpp"
#include "menu.hpp"
#include "ui_items_tab.h"

//#include <QMenu>
#include <QDataWidgetMapper>
#include <QListWidgetItem>
#include <QItemSelectionModel>

ItemsTab::ItemsTab(QWidget *parent): QWidget(parent), ui(new Ui::ItemsTab)
{
	ui->setupUi(this);
	itemEffectsListMenu = createMenu(this,
	{
		ui->actionEffectNew, ui->actionEffectEdit,
		ui->actionEffectGoTo, nullptr, ui->actionEffectDelete
	});

	effectsModel = new ItemEffectsModel(ui->itemEffectsList);
	ui->itemEffectsList->setModel(effectsModel);

	ui->itemAnimationButton->setSource(SimpleChooserDialog::ANIMATION);

	connect(ui->actionEffectNew, &QAction::triggered, this, &ItemsTab::actionEffectNewTriggered);
	connect(ui->actionEffectEdit, &QAction::triggered, this, &ItemsTab::actionEffectEditTriggered);
	connect(ui->actionEffectDelete, &QAction::triggered, this, &ItemsTab::actionEffectDeleteTriggered);
	connect(ui->actionEffectGoTo, &QAction::triggered, this, &ItemsTab::actionEffectGotToTriggered);

	connect(ui->itemEffectsList, &QTableView::customContextMenuRequested, this, &ItemsTab::contextMenuRequested);
	connect(ui->itemEffectsList, &QTableView::doubleClicked, ui->itemEffectsList, [this](const QModelIndex &) { actionEffectEditTriggered(true); });

	connect(ui->itemsTable, &BaseTable::rowSelected, this, &ItemsTab::itemRowSelected);
	connect(ui->itemNameFilter, &QLineEdit::textChanged, ui->itemsTable, &BaseTable::setFilterText);
	connect(ui->itemClearFilterButton, &QPushButton::clicked, ui->itemNameFilter, &QLineEdit::clear);
	connect(ui->itemIconLabel, &ClickableLabel::doubleClicked, this, &ItemsTab::itemIconClicked);
	connect(ui->itemDamageTypeComboBox, &QComboBox::currentIndexChanged, this, &ItemsTab::itemDamageTypeChanged);

	connect(ui->itemNewButton, &QPushButton::clicked, this, &ItemsTab::itemNewClicked);
	connect(ui->itemClearButton, &QPushButton::clicked, this, &ItemsTab::itemClearClicked);
	connect(ui->itemResizeButton, &QPushButton::clicked, this, &ItemsTab::itemResizeClicked);
	connect(ui->itemApplyButton, &QPushButton::clicked, this, &ItemsTab::applyButtonClicked);
}

ItemsTab::~ItemsTab()
{
	delete ui;
}



void ItemsTab::init()
{
	delete mapper;
	delete model;

	ui->itemIconLabel->setIconMode(ClickableLabel::Mode::ICON_SET, Images::Get()->iconSet());

	model = new ItemsModel(this);
	ui->itemsTable->setModel2(model, Images::Get()->iconSet());

	ui->itemApplyButton->setEnabled(false);
	ui->itemDamageElementComboBox->clear(); // Normal Attack and None only present in items?
	ui->itemDamageElementComboBox->addItem("Normal Attack"); // -1

	std::vector<QString> &elements = Database::Get()->system()->elements;
	for (size_t i = 0; i < elements.size(); i++) // 1..x
		if (!elements[i].isEmpty())
			ui->itemDamageElementComboBox->addItem(elements[i]);
		else
			ui->itemDamageElementComboBox->addItem(QString("#%1").arg(i, 2, 10, QChar('0')));
	ui->itemDamageElementComboBox->setItemText(1, "None");  // 0

	mapper = new DataMapper(this);
	mapper->setModel(model);
	mapper->addWidgets({
		{ ui->itemAnimationButton, Item::ANIMATION_ID },
		{ ui->itemConsumableComboBox, Item::CONSUMABLE },
		{ ui->itemDamageCriticalHitsComboBox, Item::DAMAGE_CRITICAL },
		{ ui->itemDamageElementComboBox, Item::DAMAGE_ELEMENT },
		{ ui->itemDamageFormulaEdit, Item::DAMAGE_FORMULA },
		{ ui->itemDamageTypeComboBox, Item::DAMAGE_TYPE },
		{ ui->itemDamageVarianceSpinBox, Item::DAMAGE_VARIANCE },
		{ ui->itemDescEdit, Item::DESC },
		{ ui->itemHitTypeComboBox, Item::HIT_TYPE },
		{ ui->itemIconIndexLabel, Item::ICON_INDEX },
		{ ui->itemTypeComboBox, Item::ITEM_TYPE },
		{ ui->itemNameEdit, Item::NAME },
		{ ui->itemNotes, Item::NOTE },
		{ ui->itemOccasionComboBox, Item::OCCASION },
		{ ui->itemPriceSpinBox, Item::PRICE },
		{ ui->itemRepeatSpinBox, Item::REPEAT },
		{ ui->itemScopeComboBox, Item::SCOPE },
		{ ui->itemSpeedSpinBox, Item::SPEED },
		{ ui->itemSuccessSpinBox, Item::SUCCESS },
		{ ui->itemTPGainSpinBox, Item::TP_GAIN },
	});

	ui->itemsTable->selectRow(0);

	connect(model, &QAbstractItemModel::dataChanged, model,
			[this](const QModelIndex &, const QModelIndex &, const QList<int> &)
	{ ui->itemApplyButton->setEnabled(true); });
}

void ItemsTab::itemRowSelected(int row)
{
	currentItem = model->item(row);
	if (!currentItem)
	{
		effectsModel->setEffects(nullptr);
		mapper->toFirst();
		enableGroupBoxes(false);
		return;
	}

	if (!ui->generalBox->isEnabled())
		enableGroupBoxes(true);

	mapper->setCurrentIndex(row);
	ui->itemIconLabel->setIconIndex(currentItem->iconIndex);

	effectsModel->setEffects(&currentItem->effects);
}

void ItemsTab::itemDamageTypeChanged(int index)
{
	bool toggle = index != 0;

	ui->itemDamageElementComboBox->setEnabled(toggle);
	ui->itemDamageFormulaEdit->setEnabled(toggle);
	ui->itemDamageVarianceSpinBox->setEnabled(toggle);
	ui->itemDamageCriticalHitsComboBox->setEnabled(toggle);
}

void ItemsTab::itemIconClicked()
{
	IconPickerDialog dialog(this, PickerType::ICON_SET, "", currentItem->iconIndex);
	if (dialog.exec())
	{
		int index = dialog.index();
		model->setData(model->index(currentItem->id, Item::ICON_INDEX), index, Qt::EditRole);
		ui->itemIconLabel->setIconIndex(index);
	}
}

void ItemsTab::contextMenuRequested(const QPoint &pos)
{
	if (!currentItem)
		return;

	QModelIndex index = ui->itemEffectsList->indexAt(pos);
	bool enabled = index.isValid();

	ui->actionEffectEdit->setEnabled(enabled);
	ui->actionEffectDelete->setEnabled(enabled);

	bool flag = enabled && index.data(ItemEffectsModel::CODE).toInt() == Effect::COMMON_EVENT;
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
	ItemEffectDialog dialog(currentItem->effects.at(effectIndex), this);
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
	QModelIndex index = ui->itemEffectsList->currentIndex();
	emit selectCommonEvent(index.data(ItemEffectsModel::DATA).toInt());
}


void ItemsTab::applyButtonClicked()
{
	ui->itemApplyButton->setEnabled(false);
}

void ItemsTab::enableGroupBoxes(bool enabled)
{
	if (!enabled)
		ui->itemIconLabel->setIconIndex(0);

	ui->generalBox->setEnabled(enabled);
	ui->invocationBox->setEnabled(enabled);
	ui->damageBox->setEnabled(enabled);
	ui->effectsBox->setEnabled(enabled);
	ui->notesBox->setEnabled(enabled);
}

void ItemsTab::itemNewClicked()
{
	model->insertRows(model->rowCount(), 1);
	ui->itemsTable->selectRow(model->rowCount() - 1);
}

void ItemsTab::itemResizeClicked()
{
	ChangeMaximumDialog dialog(model, ui->itemResizeButton);
	dialog.exec();
}

void ItemsTab::itemClearClicked()
{
	model->clearElement(ui->itemsTable->selectedRow());
	effectsModel->setEffects(nullptr);
}

