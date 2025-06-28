#include "map_events_tab.hpp"
#include "command_factory.hpp"
#include "map_event_page.hpp"
#include "ui_map_events_tab.h"

#include <QItemSelectionModel>


MapEventsTab::MapEventsTab(QWidget *parent): QWidget(parent), ui(new Ui::MapEventsTab)
{
	ui->setupUi(this);
}

MapEventsTab::~MapEventsTab()
{
	delete ui;
}

//void MapEventsTab::init(Map *map)
void MapEventsTab::init(TileMap *tileMap)
{
	if (model)
		delete model;

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
	model = tileMap->eventsModel();
	ui->mapEventsTable->setModel2(model);

	//connect(ui->mapEventsTable->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MapEventsTab::mapEventsTableClicked);
	connect(ui->mapEventsTable, &BaseTable::rowSelected, this, &MapEventsTab::mapEventsTableClicked);
}

//void MapEventsTab::mapEventsTableClicked(const QModelIndex &, const QModelIndex &)
void MapEventsTab::mapEventsTableClicked(int row)
{
	//int id = ui->mapEventsTable->selectedId();
	MapEvent *event = nullptr;
	if (currentMap->events()->at(row).has_value())
		event = &currentMap->events()->at(row).value();

	if (!event)
		return;

	pagesModel = new MapEventPagesModel(&event->pages, this);

	ui->mapEventPagesWidget->clear();
	for (size_t i = 0; i < event->pages.size(); i++)
	{
		MapEventPage *page = new MapEventPage(pagesModel, i, &event->pages[i], ui->mapEventPagesWidget);
		ui->mapEventPagesWidget->addTab(page, QString::number(i));
	};
}

void MapEventsTab::selectEvent(int id)
{
	ui->mapEventsTable->selectRow(id);
}

void MapEventsTab::addMapEvent(MapEvent event)
{
	model->insertRows(model->rowCount(), 1);
	currentMap->events()->at(model->rowCount() - 1) = event;
	//model->setData(model->index(model->rowCount() - 1, 0), )
}

