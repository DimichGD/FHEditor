#include "map_tab.hpp"
#include "map_event_tool.hpp"
#include "map_events_tab.hpp"
#include "map_info_model.hpp"
#include "settings.hpp"
#include "tile_paint_tool.hpp"
#include "tile_picker_tool.hpp"
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
	ui->modeButtonGroup->setId(ui->tileModeButton, 0);
	ui->modeButtonGroup->setId(ui->eventModeButton, 1);
	ui->modeButtonGroup->setId(ui->pickerModeButton, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_1, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_2, 3);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonA, 0);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonB, 1);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonC, 2);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonD, 3);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonE, 4);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButtonR, 5);

	/*tilePickerViews[0] = ui->tilePicker_A;
	tilePickerViews[1] = ui->tilePicker_B;
	tilePickerViews[2] = ui->tilePicker_C;
	tilePickerViews[3] = ui->tilePicker_D;
	tilePickerViews[4] = ui->tilePicker_E;*/

	//connect(ui->mapInfoTable, &QAbstractItemView::activated, this, &MapTab::mapInfoTableDoubleClicked);
	connect(ui->mapInfoTable, &BaseTable::rowSelected, this, &MapTab::mapInfoTableClicked);
	connect(ui->mapNameFilter, &QLineEdit::textChanged, ui->mapInfoTable, &BaseTable::setFilterText);
	//connect(ui->visibleLayersButtonGroup, &QButtonGroup::idToggled, ui->mapView, &MapView::layersToggled);

	connect(ui->toggleMapTableButton, &QPushButton::clicked, [this]()
	{
		ui->mapInfoTable->setVisible(!ui->mapInfoTable->isVisible());
		ui->toggleMapTableButton->setText(ui->mapInfoTable->isVisible() ? "-" : "+");
	});

	//connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentMode);
	connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, [this](int id)
	{
		ui->mapView->setCurrentTool(mapViewTools[id]);
		ui->mapView->setCurrentMode(id);
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


	// TODO: remember last selection
	connect(ui->tilePickerButtonGroup, &QButtonGroup::idClicked, [this](int id)
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
	});

	//mapViewTools[0] = tilePaintTool = new TilePaintTool(ui->mapView->currentScene(), this);
	mapViewTools[0] = tilePaintTool = ui->mapView->makeTool<TilePaintTool>();
	mapViewTools[1] = mapEventTool = ui->mapView->makeTool<MapEventTool>();
	mapViewTools[2] = tilePickerTool = ui->mapView->makeTool<TilePickerTool>();

	connect(ui->tilePickerView, &TilePickerView::tileSelected, tilePaintTool, &TilePaintTool::setCurrentTileSingle);
	connect(ui->tilePickerView, &TilePickerView::multipleTilesSelected, tilePaintTool, &TilePaintTool::setCurrentTileMultiple);

	connect(tilePickerTool, &TilePickerTool::pickTile,
			[this](int tileId, int buttonIndex)
	{
		ui->tilePickerButtonGroup->button(buttonIndex)->click();
		ui->tilePickerView->selectTile(tileId);
	});

	connect(ui->paintLayerButtonGroup, &QButtonGroup::idClicked, tilePaintTool, &TilePaintTool::setCurrentLayer);

	connect(mapEventTool, &MapEventTool::selectEvent, [this](int eventId)
		{ emit editMapEvent(eventId); });

	//connect(mapEventTool, &MapEventTool::newEvent, [this](int eventId)
	//	{ emit addMapEvent(eventId); });
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
	model = new MapInfoModel(ui->mapInfoTable);
	ui->mapInfoTable->setModel2(model);
	ui->mapView->clear();
	ui->modeButtonGroup->button(Settings::Get()->mapToolIndex)->click();

	if (Settings::Get()->lastTabIndex == 0 && Settings::Get()->lastMapId != 0)
	{
		ui->mapInfoTable->selectRow(Settings::Get()->lastMapId); // FIXME: filter null maps
		//mapInfoTableClicked(Settings::Get()->lastMapId);
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
		ui->tilePickerButtonGroup->button(i)->setEnabled(tileMap.hasTileSet(setIndex));
	}


	ui->mapView->load(&tileMap);
	//ui->modeButtonGroup->button(Settings::Get()->mapToolIndex)->click();

	// Set first existing tileset for tile picker
	for (int i = 0; i < 5; i++)
	{
		if (ui->tilePickerButtonGroup->button(i)->isEnabled())
		{
			ui->tilePickerButtonGroup->button(i)->click();
			break;
		}
	}

	ui->tilePickerView->selectPoint(QPoint(0, 0));
	Settings::Get()->lastMapId = id;
}

void MapTab::mapInfoTableClicked(int row)
{
	uint64_t start = QDateTime::currentMSecsSinceEpoch();

	//int id = ui->mapInfoTable->selectedRow();
	currentMapId = row;
	loadMap(row);
	//emit mapLoaded(currentMap);
	emit mapLoaded(&tileMap);

	uint64_t end = QDateTime::currentMSecsSinceEpoch();
	emit mapLoadTime(end - start);
}


