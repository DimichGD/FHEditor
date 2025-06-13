#include "map_events_tab.hpp"
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

void MapEventsTab::init(Map *map)
{
	currentMap = map;

	model = new MapEventsModel(map, ui->mapEventsTable);
	ui->mapEventsTable->setModel2(model);

	connect(ui->mapEventsTable->selectionModel(), &QItemSelectionModel::currentRowChanged, this, &MapEventsTab::mapEventsTableDoubleClicked);
}

void MapEventsTab::mapEventsTableDoubleClicked(const QModelIndex &, const QModelIndex &)
{
	int id = ui->mapEventsTable->selectedId();
	MapEvent *event = nullptr;
	if (currentMap->events[id].has_value())
		event = &currentMap->events[id].value();

	if (!event)
		return;

	pagesModel = new MapEventPagesModel(&event->pages, this);

	ui->mapEventPagesWidget->clear();
	for (size_t i = 0; i < event->pages.size(); i++)
	{
		MapEventPage *page = new MapEventPage(pagesModel, i, &event->pages[i], this);
		ui->mapEventPagesWidget->addTab(page, QString::number(i));
	}
}

void MapEventsTab::selectEvent(int id)
{
	ui->mapEventsTable->selectRow(id);
}

