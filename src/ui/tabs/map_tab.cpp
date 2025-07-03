#include "map_tab.hpp"
#include "map_event_tool.hpp"
#include "map_events_tab.hpp"
#include "map_info_model.hpp"
#include "settings.hpp"
#include "tile_paint_tool.hpp"
#include "tile_picker_tool.hpp"
#include "ui_map_tab.h"
#include "command_factory.hpp"
#include "database.hpp"

#include <QButtonGroup>
#include <QDateTime>
#include <QProcess>



MapTab::MapTab(QWidget *parent): BaseTab(parent), ui(new Ui::MapTab)
{
	ui->setupUi(this);

	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_0, 0);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_1, 1);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_2, 2);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_3, 3);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_4, 4);
	ui->visibleLayersButtonGroup->setId(ui->layerCheckBox_5, 5);
	ui->modeButtonGroup->setId(ui->tileModeButton, 0);
	ui->modeButtonGroup->setId(ui->eventModeButton, 1);
	ui->modeButtonGroup->setId(ui->pickerModeButton, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_1, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_2, 3);
	/*ui->tilePickerButtonGroup->setId(ui->tilePickerButton_A, 0);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_B, 1);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_C, 2);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_D, 3);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_E, 4);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_R, 5);*/

	expandIcon = QIcon(":/icons8-expand-48.png");
	collapseIcon = QIcon(":/icons8-collapse-arrow-48.png");

	model = new MapInfoModel(this);
	ui->mapInfoTable->setModel2(model, MapInfo::NAME);

	//connect(ui->mapInfoTable, &QAbstractItemView::activated, this, &MapTab::mapInfoTableDoubleClicked);
	connect(ui->mapInfoTable, &BaseTable::rowSelected, this, &MapTab::mapInfoTableClicked);
	connect(ui->mapNameFilter, &QLineEdit::textChanged, ui->mapInfoTable, &BaseTable::setFilterText);
	//connect(ui->visibleLayersButtonGroup, &QButtonGroup::idToggled, ui->mapView, &MapView::layersToggled);

	connect(ui->toggleMapTableButton, &QPushButton::clicked, [this]()
	{
		ui->mapInfoWidget->setVisible(!ui->mapInfoWidget->isVisible());
		ui->toggleMapTableButton->setIcon(ui->mapInfoTable->isVisible() ? expandIcon : collapseIcon);
	});

	//connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentMode);
	connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, [this](int id)
	{
		ui->mapView->setCurrentTool(mapViewTools[id]);
		ui->mapView->setCurrentMode(id);
		ui->stackedWidget->setCurrentIndex(mapViewTools[id] == mapEventTool ? 1 : 0);
	});


	connect(ui->runButton, &QPushButton::clicked, [this]()
	{
		if (Settings::Get()->rpgmPath.isEmpty())
			return;

		QString path = Settings::Get()->lastPath;
		QStringList arguments { path, "test&tskip" };

		process = new QProcess(this); // FIXME: check rpgmPath is valid path
		process->start(Settings::Get()->rpgmPath + "/nwjs-lnx-test/Game", arguments);
	});


	// TODO: remember last selection
	/*connect(ui->tilePickerButtonGroup, &QButtonGroup::idClicked, [this](int id)
	{
		TileSet::Set setIndex = TileSet::Set(TileSet::A5 + id);
		ui->tilePickerView->setBackgroundPixmap(setIndex, 48, tileMap.pixmap(setIndex));

		if (id == 0)
		{
			//ui->mapView->setCurrentLayer(0);
			tilePaintTool->setCurrentLayer(0);
			ui->layerButton_1->setEnabled(false);
			ui->layerButton_2->setEnabled(false);
		}
		else
		{
			//ui->mapView->setCurrentLayer(ui->paintLayerButtonGroup->checkedId());
			tilePaintTool->setCurrentLayer(ui->paintLayerButtonGroup->checkedId());
			ui->layerButton_1->setEnabled(true);
			ui->layerButton_2->setEnabled(true);
		}
	});*/

	//mapViewTools[0] = tilePaintTool = new TilePaintTool(ui->mapView->currentScene(), this);
	mapViewTools[0] = tilePaintTool = ui->mapView->makeTool<TilePaintTool>();
	mapViewTools[1] = mapEventTool = ui->mapView->makeTool<MapEventTool>();
	mapViewTools[2] = tilePickerTool = ui->mapView->makeTool<TilePickerTool>();

	//connect(ui->tilePickerView, &TilePickerView::tileSelected, tilePaintTool, &TilePaintTool::setCurrentTileSingle);
	//connect(ui->tilePickerView, &TilePickerView::multipleTilesSelected, tilePaintTool, &TilePaintTool::setCurrentTileMultiple);

	/*connect(tilePickerTool, &TilePickerTool::pickTile,
			[this](int tileId, int buttonIndex)
	{
		ui->tilePickerButtonGroup->button(buttonIndex)->click();
		ui->tilePickerView->selectTile(tileId);
	});*/

	connect(ui->paintLayerButtonGroup, &QButtonGroup::idClicked, tilePaintTool, &TilePaintTool::setCurrentLayer);

	//connect(mapEventTool, &MapEventTool::selectEvent, [this](int eventId)
	//	{ emit editMapEvent(eventId); });
	connect(mapEventTool, &MapEventTool::selectEvent, this, &MapTab::selectMapEvent);

	for (int i = 0; i < MapInfo::COUNT; i++)
		ui->mapInfoTable->setColumnHidden(i, true);

	ui->mapInfoTable->setColumnHidden(MapInfo::ID, false);
	ui->mapInfoTable->setColumnHidden(MapInfo::NAME, false);
	ui->mapInfoTable->resizeColumnToContents(MapInfo::ID);
}

MapTab::~MapTab()
{
	for (auto tool: mapViewTools)
		delete tool;

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
	model->reset();
	ui->mapView->clear();
	ui->modeButtonGroup->button(Settings::Get()->mapToolIndex)->setChecked(true);

	int toolIndex = Settings::Get()->mapToolIndex;
	ui->mapView->setCurrentTool(mapViewTools.at(toolIndex));
	ui->stackedWidget->setCurrentIndex(toolIndex == 1 ? 1 : 0);

	ui->mapInfoTable->setCurrentIndex(QModelIndex());
	//if (Settings::Get()->lastTabIndex == 0)
	{
		ui->mapInfoTable->selectRow(Settings::Get()->lastTableRow); // FIXME: filter null maps
		// FIXME: load last map only on app start
	}
}

void MapTab::loadMap(int id)
{
	ui->mapView->clear();
	//currentMap = Database::Get()->map(id);

	const auto buttons = ui->visibleLayersButtonGroup->buttons();
	for (auto checkBox: buttons)
	{
		checkBox->setChecked(true);
		checkBox->setEnabled(true);
	}

	tileMap.loadTileMap(id);
	for (auto tool: mapViewTools)
		tool->setTileMap(&tileMap);

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
		//ui->tilePickerButtonGroup->button(i)->setEnabled(tileMap.hasTileSet(setIndex));
	}

	Map *map = Database::Get()->map(id);
	ui->tilePickerWidget->setTileSet(map->tilesetId);

	ui->mapView->load(&tileMap);

	// Set first existing tileset for tile picker
	/*for (int i = 0; i < 5; i++)
	{
		if (ui->tilePickerButtonGroup->button(i)->isEnabled())
		{
			ui->tilePickerButtonGroup->button(i)->click();
			break;
		}
	}*/

	//ui->tilePickerView->selectPoint(QPoint(0, 0));
	ui->mapToolBar->setEnabled(true);
}

void MapTab::mapInfoTableClicked(int row)
{
	//uint64_t start = QDateTime::currentMSecsSinceEpoch();

	//int id = ui->mapInfoTable->selectedRow();
	if (row < 0)
	{
		ui->mapToolBar->setEnabled(false);
		return;
	}
	//currentMapId = model->mapInfo(row)->id;
	loadMap(model->mapInfo(row)->id);
	Settings::Get()->lastTableRow = row; // FIXME: fucking off by one thing
	//emit mapLoaded(currentMap);
	emit mapLoaded(&tileMap);

	//uint64_t end = QDateTime::currentMSecsSinceEpoch();
	//emit mapLoadTime(end - start);
}


