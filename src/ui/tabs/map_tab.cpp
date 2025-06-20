#include "map_tab.hpp"
#include "map_events_tab.hpp"
#include "map_info_model.hpp"
#include "settings.hpp"
#include "ui_map_tab.h"
#include "command_factory.hpp"

#include <QButtonGroup>
#include <QDateTime>
#include <QProcess>

MapTab::MapTab(QWidget *parent): QWidget(parent), ui(new Ui::MapTab)
{
	ui->setupUi(this);

	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_0, 0);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_1, 1);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_2, 2);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_3, 3);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_4, 4);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_5, 5);
	ui->modeButtonGroup->setId(ui->tileModeButton, MapView::Mode::TILES);
	ui->modeButtonGroup->setId(ui->eventModeButton, MapView::Mode::EVENTS);
	ui->modeButtonGroup->setId(ui->pickerModeButton, MapView::Mode::PICKER);
	ui->paintLayerButtonGroup->setId(ui->layerButton_1, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_2, 3);

	tilePickerViews[0] = ui->tilePicker_A;
	tilePickerViews[1] = ui->tilePicker_B;
	tilePickerViews[2] = ui->tilePicker_C;
	tilePickerViews[3] = ui->tilePicker_D;
	tilePickerViews[4] = ui->tilePicker_E;

	//connect(ui->mapInfoTable, &QAbstractItemView::activated, this, &MapTab::mapInfoTableDoubleClicked);
	connect(ui->mapInfoTable, &BaseTable::rowSelected, this, &MapTab::mapInfoTableClicked);
	connect(ui->mapNameFilter, &QLineEdit::textChanged, ui->mapInfoTable, &BaseTable::setFilterText);
	connect(ui->visibleLayersButtonGroup, &QButtonGroup::idToggled, ui->mapView, &MapView::layersToggled);

	connect(ui->toggleMapTableButton, &QPushButton::clicked, [this]()
	{
		ui->mapInfoTable->setVisible(!ui->mapInfoTable->isVisible());
		ui->toggleMapTableButton->setText(ui->mapInfoTable->isVisible() ? "-" : "+");
	});

	connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentMode);
	connect(ui->paintLayerButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentLayer);

	connect(ui->tilesTabWidget, &QTabWidget::currentChanged, ui->tilesTabWidget, [this](int index)
	{
		if (index == 0)
		{
			ui->mapView->setCurrentLayer(0);
			ui->layerButton_1->setEnabled(false);
			ui->layerButton_2->setEnabled(false);
		}
		else
		{
			ui->mapView->setCurrentLayer(ui->paintLayerButtonGroup->checkedId());
			ui->layerButton_1->setEnabled(true);
			ui->layerButton_2->setEnabled(true);
		}
	});

	connect(ui->tilePicker_A, &TilePickerView::tileSelected, ui->mapView, &MapView::setCurrentTileSingle);
	connect(ui->tilePicker_B, &TilePickerView::tileSelected, ui->mapView, &MapView::setCurrentTileSingle);
	connect(ui->tilePicker_C, &TilePickerView::tileSelected, ui->mapView, &MapView::setCurrentTileSingle);
	connect(ui->tilePicker_D, &TilePickerView::tileSelected, ui->mapView, &MapView::setCurrentTileSingle);
	connect(ui->tilePicker_E, &TilePickerView::tileSelected, ui->mapView, &MapView::setCurrentTileSingle);

	connect(ui->tilePicker_A, &TilePickerView::multipleTilesSelected, ui->mapView, &MapView::setCurrentTileMultiple);
	connect(ui->tilePicker_B, &TilePickerView::multipleTilesSelected, ui->mapView, &MapView::setCurrentTileMultiple);
	connect(ui->tilePicker_C, &TilePickerView::multipleTilesSelected, ui->mapView, &MapView::setCurrentTileMultiple);
	connect(ui->tilePicker_D, &TilePickerView::multipleTilesSelected, ui->mapView, &MapView::setCurrentTileMultiple);
	connect(ui->tilePicker_E, &TilePickerView::multipleTilesSelected, ui->mapView, &MapView::setCurrentTileMultiple);

	connect(ui->saveButton, &QPushButton::clicked, [this]()
	{
		Database::Get()->saveMap(currentMapId);
	});

	connect(ui->runButton, &QPushButton::clicked, [this]()
	{
		if (Settings::Get()->rpgmPath.isEmpty())
			return;

		QString path = Settings::Get()->lastPath;
		QStringList arguments { path, "test" };

		process = new QProcess(this); // FIXME: check rpgmPath is valid path
		process->start(Settings::Get()->rpgmPath + "/nwjs-lnx-test/Game", arguments);
	});

	connect(ui->mapView, &MapView::editEvent, [this](int eventId)
	{
		/*MapEventsTab *mapEventsTab = new MapEventsTab();
		mapEventsTab->resize(1280, 720);
		mapEventsTab->setWindowModality(Qt::ApplicationModal);
		mapEventsTab->init(currentMap);
		mapEventsTab->selectEvent(eventId);
		mapEventsTab->show();*/

		emit editMapEvent(eventId);
	});

	connect(ui->mapView, &MapView::newEvent, [this](int x, int y)
	{
		/*MapEventsTab *mapEventsTab = new MapEventsTab(nullptr, true);
		mapEventsTab->resize(1280, 720);
		mapEventsTab->setWindowModality(Qt::ApplicationModal);
		mapEventsTab->init(currentMap);
		mapEventsTab->selectEvent(eventId);
		mapEventsTab->show();*/

		bool updateExisting = false;
		auto it = std::next(currentMap->events.begin());
		while (it != currentMap->events.end())
		{
			if (!it->has_value())
			{
				updateExisting = true;
				break;
			}

			std::advance(it, 1);
		}

		//int lastEventId = currentMap->events.back().value().id + 1;
		int lastEventId = std::prev(it)->value().id + 1;
		MapEvent event {};
		event.id = lastEventId;
		event.name = QString("EV%1").arg(lastEventId, 3, 10, QChar('0'));
		event.x = x;
		event.y = y;
		event.pages.emplace_back();
		event.pages.back().list.push_back({ CommandFactory::ZERO, 0, CommandFactory::createCommand2(0) });

		if (updateExisting)
		{
			*it = event;
			emit editMapEvent(lastEventId);
		}

		else
		{
			//currentMap->events.push_back(event);
			emit addMapEvent(event);
		}

		ui->mapView->addNewEvent(event);
	});

	connect(ui->mapView, &MapView::pickTile, [this](int tileId)
	{
		TileSet::Set setIndex = tilesetIndexFromId(tileId);
		if (setIndex >= TileSet::A1 && setIndex <= TileSet::A5)
			ui->tilesTabWidget->setCurrentIndex(0);
		else
			ui->tilesTabWidget->setCurrentIndex(setIndex - 4);

		TilePickerView *view = tilePickerViews[ui->tilesTabWidget->currentIndex()];
		view->selectTile(tileId);
	});
}

MapTab::~MapTab()
{
	if (process)
	{
		process->terminate();
		process->waitForFinished(5000);
		delete process;
	}

	delete ui;
}

void MapTab::init()
{
	model = new MapInfoModel(ui->mapInfoTable);
	ui->mapInfoTable->setModel2(model);
}

void MapTab::loadMap(int id)
{
	uint64_t start = QDateTime::currentMSecsSinceEpoch();
	currentMap = Database::Get()->map(id);
	ui->mapView->clear();

	const auto buttons = ui->visibleLayersButtonGroup->buttons();
	for (auto checkBox: buttons)
	{
		checkBox->setChecked(true);
		checkBox->setEnabled(true);
	}

	tileMap.loadTileMap(id);

	for (int layer = 0; layer < 6; layer++) // 6 - region
	{
		bool empty = true;
		for (int y = 0; y < tileMap.height(); y++)
		{
			for (int x = 0; x < tileMap.width(); x++)
			{
				int tileId = tileMap.tileId(x, y, layer);
				if (tileId == 0)
					continue;

				empty = false;
			}
		}

		if (empty)
		{
			ui->visibleLayersButtonGroup->button(layer)->setChecked(false);
			ui->visibleLayersButtonGroup->button(layer)->setEnabled(false);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		TileSet::Set setIndex = TileSet::Set(TileSet::A5 + i);
		if (tileMap.hasTileSet(setIndex))
		{
			tilePickerViews[i]->setBackgroundPixmap(setIndex, 48, tileMap.pixmap(setIndex));
			ui->tilesTabWidget->setTabEnabled(i, true);
		}
		else
		{
			tilePickerViews[i]->setBackgroundPixmap(setIndex, 48, nullptr);
			ui->tilesTabWidget->setTabEnabled(i, false);
		}
	}

	ui->mapView->load(currentMap, &tileMap);
	ui->modeButtonGroup->button(Settings::Get()->mapToolIndex)->click();

	uint64_t end = QDateTime::currentMSecsSinceEpoch();
	emit mapLoadTime(end - start);
}

void MapTab::mapInfoTableClicked(int row)
{
	//int id = ui->mapInfoTable->selectedRow();
	currentMapId = row;
	loadMap(row);
	emit mapLoaded(currentMap);
}
