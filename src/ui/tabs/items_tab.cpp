#include "items_tab.hpp"
#include "change_maximum_dialog.hpp"
#include "icon_picker_dialog.hpp"
#include "database.hpp"
//#include "iconset.hpp"
#include "images.hpp"
#include "item_effect_dialog.hpp"
#include "data_mapper.hpp"
#include "items_model.hpp"
#include "ui_items_tab.h"

#include <QMenu>
#include <QDataWidgetMapper>
#include <QListWidgetItem>
#include <QItemSelectionModel>

ItemsTab::ItemsTab(QWidget *parent): QWidget(parent), ui(new Ui::ItemsTab)
{
	ui->setupUi(this);
	ui->itemAnimationButton->setSource(SimpleChooserDialog::ANIMATION);
	itemEffectsListMenu = new QMenu(this);
	itemEffectsListMenu->addAction(ui->actionEffectNew);
	itemEffectsListMenu->addAction(ui->actionEffectEdit);
	itemEffectsListMenu->addAction(ui->actionEffectGoTo);
	itemEffectsListMenu->addSeparator();
	itemEffectsListMenu->addAction(ui->actionEffectDelete);

	connect(ui->actionEffectNew, &QAction::triggered, this, &ItemsTab::actionEffectNewTriggered);
	connect(ui->actionEffectEdit, &QAction::triggered, this, &ItemsTab::actionEffectEditTriggered);
	connect(ui->actionEffectDelete, &QAction::triggered, this, &ItemsTab::actionEffectDeleteTriggered);

	connect(ui->itemEffectsList, &QTableWidget::customContextMenuRequested, this, &ItemsTab::contextMenuRequested);
	connect(ui->itemEffectsList, &QTableWidget::doubleClicked, [this](const QModelIndex &) { actionEffectEditTriggered(true); });

	connect(ui->itemsTable, &BaseTable::rowSelected, this, &ItemsTab::itemRowSelected);
	connect(ui->itemNameFilter, &QLineEdit::textChanged, ui->itemsTable, &BaseTable::setFilterText);
	connect(ui->itemClearFilterButton, &QPushButton::clicked, ui->itemNameFilter, &QLineEdit::clear);
	connect(ui->itemIconLabel, &ClickableLabel::doubleClicked, this, &ItemsTab::itemIconClicked);
	connect(ui->itemDamageTypeComboBox, &QComboBox::currentIndexChanged, this, &ItemsTab::itemDamageTypeChanged);

	connect(ui->itemNewButton, &QPushButton::clicked, this, &ItemsTab::itemNewClicked);
	connect(ui->itemClearButton, &QPushButton::clicked, this, &ItemsTab::itemClearClicked);
	connect(ui->itemChangeMaximumButton, &QPushButton::clicked, this, &ItemsTab::itemChangeMaximumClicked);
	connect(ui->itemApplyButton, &QPushButton::clicked, this, &ItemsTab::applyButtonClicked);
}

ItemsTab::~ItemsTab()
{
	delete ui;
}

void ItemsTab::changeIcon(int index)
{
	if (!currentItem)
		return;

	currentItem->iconIndex = index;
	ui->itemIconIndexLabel->setText(QString::number(index));
	ui->itemIconLabel->setIconIndex(index);
	emit model->dataChanged(model->index(currentItem->id, 1), model->index(currentItem->id, 1));
	// TODO: make an update(row, column) method?
}

void ItemsTab::init()
{
	// TODO: delete and nullify model pointer
	// delete via deleteLater() ?
	ui->itemIconLabel->setIconMode(ClickableLabel::Mode::ICON_SET, Images::Get()->iconSet());

	model = new ItemsModel(ui->itemsTable);
	ui->itemsTable->setModel2(model);

	ui->itemApplyButton->setEnabled(false);
	ui->itemDamageElementComboBox->clear(); // Normal Attack and None only present in items?
	ui->itemDamageElementComboBox->addItem("Normal Attack"); // -1
	for (std::string &elementName: Database::Get()->system()->elements) // 1..x
		if (!elementName.empty())
			ui->itemDamageElementComboBox->addItem(QString::fromStdString(elementName));
		else
			ui->itemDamageElementComboBox->addItem("Empty element");
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

	connect(model, &QAbstractItemModel::dataChanged,
			[this](const QModelIndex &, const QModelIndex &, const QList<int> &)
	{ ui->itemApplyButton->setEnabled(true); });
}

void ItemsTab::itemRowSelected(int row)
{
	currentItem = model->item(row);
	if (!currentItem)
	{
		ui->itemEffectsList->setRowCount(0);
		mapper->toFirst();
		enableGroupBoxes(false);
		return;
	}

	if (!ui->generalBox->isEnabled())
		enableGroupBoxes(true);

	mapper->setCurrentIndex(row);
	ui->itemIconLabel->setIconIndex(currentItem->iconIndex);

	ui->itemEffectsList->setRowCount(0);
	for (auto effect: currentItem->effects)
	{
		int lastRow = ui->itemEffectsList->rowCount();
		ui->itemEffectsList->insertRow(lastRow);

		auto stringList = effectToStringList(&effect);
		QTableWidgetItem *item = new QTableWidgetItem(stringList.at(0));
		item->setData(Qt::UserRole, lastRow);
		ui->itemEffectsList->setItem(lastRow, 0, item);
		ui->itemEffectsList->setItem(lastRow, 1, new QTableWidgetItem(stringList.at(1)));
	}
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
	if (!currentItem)
		return;

	IconPickerDialog dialog(this, currentItem->iconIndex);
	connect(&dialog, &QDialog::accepted,
		[this, &dialog]() { changeIcon(dialog.index()); });

	dialog.exec();
}

void ItemsTab::contextMenuRequested(const QPoint &pos)
{
	bool enabled = (ui->itemEffectsList->itemAt(pos) != nullptr);

	ui->actionEffectEdit->setEnabled(enabled);
	ui->actionEffectGoTo->setEnabled(enabled);
	ui->actionEffectDelete->setEnabled(enabled);

	itemEffectsListMenu->exec(ui->itemEffectsList->viewport()->mapToGlobal(pos));
}

void ItemsTab::actionEffectNewTriggered(bool)
{
	if (!currentItem)
		return;

	Effect effect {};
	currentItem->effects.push_back(effect);

	int lastRow = ui->itemEffectsList->rowCount();
	ui->itemEffectsList->insertRow(lastRow);

	auto stringList = effectToStringList(&effect);
	QTableWidgetItem *item = new QTableWidgetItem(stringList[0]);
	item->setData(Qt::UserRole, lastRow);
	ui->itemEffectsList->setItem(lastRow, 0, item);
	ui->itemEffectsList->setItem(lastRow, 1, new QTableWidgetItem(stringList[1]));
	ui->itemEffectsList->selectRow(lastRow);
}

void ItemsTab::actionEffectEditTriggered(bool)
{
	auto list = ui->itemEffectsList->selectedItems();
	if (list.empty() || !currentItem)
		return;

	int effectIndex = list[0]->data(Qt::UserRole).toInt();
	ItemEffectDialog dialog(currentItem->effects.at(effectIndex), this);
	if (dialog.exec())
	{
		Effect effect = dialog.value();
		auto stringList = effectToStringList(&effect);
		ui->itemEffectsList->item(list[0]->row(), 0)->setData(Qt::DisplayRole, stringList[0]);
		ui->itemEffectsList->item(list[0]->row(), 1)->setData(Qt::DisplayRole, stringList[1]);
		currentItem->effects[effectIndex] = effect;
	}
}

void ItemsTab::actionEffectDeleteTriggered(bool)
{
	auto list = ui->itemEffectsList->selectedItems();
	if (list.empty() || !currentItem)
		return;

	ui->itemEffectsList->removeRow(list[0]->row());
}

void ItemsTab::actionEffectGotToTriggered(bool)
{
	/*	QTabWidget *tabWidget = dynamic_cast<QTabWidget *>(parent()->parent()); // FIXME: hack?
	int code = itemEffectsList->model()->index(row, 0).data(Qt::UserRole).toInt();
	int dataId = itemEffectsList->model()->index(row, 1).data(Qt::UserRole).toInt();
	if (code == 44)
	{
		tabWidget->setCurrentIndex(4);
		tabWidget->findChild<EventsTable *>("eventsTable")->selectRow(dataId);
	}*/
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
	int rowCount = model->rowCount();
	model->insertRows(rowCount, 1);
	ui->itemsTable->selectRow(rowCount - 1);
}

void ItemsTab::itemChangeMaximumClicked()
{
	ChangeMaximumDialog dialog(model, ui->itemChangeMaximumButton);
	dialog.exec();
}

void ItemsTab::itemClearClicked()
{
	model->clearItem(ui->itemsTable->selectedRow());
	ui->itemEffectsList->setRowCount(0);
}

