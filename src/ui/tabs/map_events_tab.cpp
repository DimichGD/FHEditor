#include "map_events_tab.hpp"
#include "command_factory.hpp"
#include "map_event_page.hpp"
#include "ui_map_events_tab.h"

#include <QItemSelectionModel>




MapEventsTab::MapEventsTab(QWidget *parent): QWidget(parent), ui(new Ui::MapEventsTab)
{
	ui->setupUi(this);

	pagesTabBar = new QTabBar(this);
	pagesTabBar->setExpanding(false);
	pagesTabBar->setDocumentMode(false);
	pagesTabBar->setDrawBase(true);
	pagesTabBar->addTab("0");
	ui->mapEventPagesLayout->insertWidget(0, pagesTabBar);

	ui->switch1Button->setSource(SimpleChooserDialog::SWITCH);
	ui->switch2Button->setSource(SimpleChooserDialog::SWITCH);
	ui->variableButton->setSource(SimpleChooserDialog::VARIABLE);
	ui->itemButton->setSource(SimpleChooserDialog::ITEM);

	model = new MapEventsModel(this);

	pagesModel = new MapEventPagesModel(this);
	pagesMapper = new DataMapper(pagesModel, this);
	pagesMapper->add(ui->actorCheckBox, Page::COND_ACTOR_VALID);
	pagesMapper->add(ui->itemCheckBox, Page::COND_ITEM_VALID);
	pagesMapper->add(ui->itemButton, Page::COND_ITEM_ID);
	pagesMapper->add(ui->selfSwitchCheckBox, Page::COND_SELF_SWITCH_VALID);
	pagesMapper->add(ui->selfSwitchComboBox, Page::COND_SELF_SWITCH_CHAR);
	pagesMapper->add(ui->switch1CheckBox, Page::COND_SWITCH_1_VALID);
	pagesMapper->add(ui->switch1Button, Page::COND_SWITCH_1_ID);
	pagesMapper->add(ui->switch2CheckBox, Page::COND_SWITCH_2_VALID);
	pagesMapper->add(ui->switch2Button, Page::COND_SWITCH_2_ID);
	pagesMapper->add(ui->variableCheckBox, Page::COND_VARIABLE_VALID);
	pagesMapper->add(ui->variableButton, Page::COND_VARIABLE_ID);
	pagesMapper->add(ui->directionFixCheckBox, Page::DIRECTION_FIX);
	pagesMapper->add(ui->movementFreqComboBox, Page::MOVE_FREQ);
	pagesMapper->add(ui->movementSpeedComboBox, Page::MOVE_SPEED);
	pagesMapper->add(ui->movementTypeComboBox, Page::MOVE_TYPE);
	pagesMapper->add(ui->priorityComboBox, Page::PRIORITY_TYPE);
	pagesMapper->add(ui->steppingCheckBox, Page::STEP_ANIME);
	pagesMapper->add(ui->throughCheckBox, Page::THROUGH);
	pagesMapper->add(ui->triggerComboBox, Page::TRIGGER);
	pagesMapper->add(ui->walkingCheckBox, Page::WALK_ANIME);

	connectCheckBoxToWidget(ui->selfSwitchCheckBox, ui->selfSwitchComboBox);
	connectCheckBoxToWidget(ui->switch1CheckBox, ui->switch1Button);
	connectCheckBoxToWidget(ui->switch2CheckBox, ui->switch2Button);
	connectCheckBoxToWidget(ui->variableCheckBox, ui->variableButton);
	connectCheckBoxToWidget(ui->variableCheckBox, ui->variableSpinBox);
	connectCheckBoxToWidget(ui->itemCheckBox, ui->itemButton);
	connectCheckBoxToWidget(ui->actorCheckBox, ui->actorButton);

	enableWidgets(false);
}

MapEventsTab::~MapEventsTab()
{
	delete ui;
}

//void MapEventsTab::init(Map *map)
void MapEventsTab::init(TileMap *tileMap)
{
	//if (model)
	//	delete model;

	currentMap = tileMap;

	/*if (newEvent)
	{
		int lastEventId = map->events.back().value().id;
		MapEvent event {};
		event.id = lastEventId + 1;
		event.name = QString("EV%1").arg(lastEventId + 1, 3, 10, QChar('0'));
		event.pages.emplace_back();
		event.pages.back().list.push_back({ CommandFactory::ZERO, 0, CommandFactory::createCommand2(0) });
		map->events.push_back(event);
	}*/

	//model = new MapEventsModel(tileMap->events(), ui->mapEventsTable);
	//model = tileMap->eventsModel();
	tileMap->setEventsModel(model);
	ui->mapEventsTable->setModel2(model, MapEvent::NAME);
	ui->mapEventsTable->setColumnHidden(MapEvent::NOTE, true);
	ui->mapEventsTable->setColumnHidden(MapEvent::POS_X, true);
	ui->mapEventsTable->setColumnHidden(MapEvent::POS_Y, true);
	ui->mapEventsTable->resizeColumnToContents(0);

	mapper = new DataMapper(model, this);
	mapper->add(ui->mapEventNameEdit, MapEvent::NAME);
	mapper->add(ui->mapEventNoteEdit, MapEvent::NOTE);

	//connect(ui->mapEventsTable->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MapEventsTab::mapEventsTableClicked);
	connect(ui->mapEventsTable, &BaseTable::rowSelected, this, &MapEventsTab::mapEventsTableClicked);
	connect(ui->mapEventsNameFilter, &QLineEdit::textEdited, ui->mapEventsTable, &BaseTable::setFilterText);
	connect(pagesTabBar, &QTabBar::currentChanged, this, &MapEventsTab::setCurrentPage);
}

//void MapEventsTab::mapEventsTableClicked(const QModelIndex &, const QModelIndex &)
void MapEventsTab::mapEventsTableClicked(int row)
{
	//int id = ui->mapEventsTable->selectedId();
	MapEvent *event = model->mapEvent(row);
	//if (currentMap->events()->at(row).has_value())
	//	event = &currentMap->events()->at(row).value();

	if (!event)
	{
		enableWidgets(false);
		mapper->setCurrentIndex(-1);
		pagesMapper->setCurrentIndex(-1);
		return;
	}

	for (int i = pagesTabBar->count() - 1; i >= 0; i--)
		pagesTabBar->removeTab(i);

	/*ui->mapEventPagesWidget->clear();
	for (auto widget: pageWidgets)
		delete widget;*/

	//pageWidgets.clear();

	mapper->setCurrentIndex(row);
	pagesModel->setPages(&event->pages);

	/*Page *page = pagesModel->page(0);
	ui->eventContentList->loadList(&page->list);
	//ui->imageLabel->setIconImage({}); // TODO: make clear method or comething
	if (!page->image.characterName.isEmpty())
		if (page->image.tileId == 0)
			ui->imageLabel->setIconImage(page->image);*/

	// TODO: check if pages size is 0
	setCurrentPage(0);

	for (size_t i = 0; i < event->pages.size(); i++)
	{
		//MapEventPage *page = new MapEventPage(pagesModel, i, ui->mapEventPagesWidget);
		//ui->mapEventPagesWidget->addTab(page, QString::number(i));
		//pageWidgets.push_back(page);
		pagesTabBar->addTab(QString::number(i));
	};

	enableWidgets(true);
}

void MapEventsTab::selectEvent(int id)
{
	ui->mapEventsTable->selectRow(id);
}

void MapEventsTab::addMapEvent(MapEvent event)
{
	//model->insertRows(model->rowCount(), 1);
	//currentMap->events()->at(model->rowCount() - 1) = event;
}

void MapEventsTab::connectCheckBoxToWidget(QCheckBox *checkBox, QWidget *widget)
{
	connect(checkBox, &QCheckBox::stateChanged, this,
			[widget](int state)
			{ widget->setEnabled(state == Qt::Checked); });
}

void MapEventsTab::enableWidgets(bool enabled)
{
	pagesTabBar->setDisabled(!enabled);
	ui->mapEventPageWidget->setEnabled(enabled);
	ui->toolBarWidget->setEnabled(enabled);
}

void MapEventsTab::setCurrentPage(int index)
{
	pagesMapper->setCurrentIndex(index);
	if (index < 0)
		return;

	Page *page = pagesModel->page(index);
	ui->eventContentList->loadList(&page->list);
	//ui->imageLabel->setIconImage({}); // TODO: make clear method or comething
	if (!page->image.characterName.isEmpty())
		if (page->image.tileId == 0)
			ui->imageLabel->setIconImage(page->image);
}
