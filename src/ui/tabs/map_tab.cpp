#include "map_tab.hpp"
#include "map_events_tab.hpp"
#include "map_info_model.hpp"
#include "ui_map_tab.h"

#include <QButtonGroup>
#include <QDateTime>
#include <QProcess>
#include <QSettings>

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
	//ui->paintLayerButtonGroup->setId(ui->layerButton_0, 0);
	ui->paintLayerButtonGroup->setId(ui->layerButton_1, 2);
	ui->paintLayerButtonGroup->setId(ui->layerButton_2, 3);

	tilePickerViews[0] = ui->tilePicker_A;
	tilePickerViews[1] = ui->tilePicker_B;
	tilePickerViews[2] = ui->tilePicker_C;
	tilePickerViews[3] = ui->tilePicker_D;
	tilePickerViews[4] = ui->tilePicker_E;

	//connect(ui->mapInfoTable, &QAbstractItemView::activated, this, &MapTab::mapInfoTableDoubleClicked);
	connect(ui->mapInfoTable, &QAbstractItemView::clicked, this, &MapTab::mapInfoTableDoubleClicked);
	connect(ui->mapNameFilter, &QLineEdit::textChanged, ui->mapInfoTable, &BaseTable::setFilterText);
	//connect(ui->visibleLayersButtonGroup, &QButtonGroup::idToggled, ui->mapView, &MapView::layersToggled);
	connect(ui->mapView, &MapView::layerIsEmpty, ui->visibleLayersButtonGroup, [this](int index)
	{
		ui->visibleLayersButtonGroup->button(index)->setChecked(false);
		ui->visibleLayersButtonGroup->button(index)->setEnabled(false);
	});

	connect(ui->toggleMapTableButton, &QPushButton::clicked, [this]()
	{
		ui->mapInfoTable->setVisible(!ui->mapInfoTable->isVisible());
		ui->toggleMapTableButton->setText(ui->mapInfoTable->isVisible() ? "-" : "+");
	});

	connect(ui->modeButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentMode);
	/*{
		ui->mapView->currentMode = MapView::Mode(id);
		ui->mapView->updateEventTiles();
	});*/

	connect(ui->paintLayerButtonGroup, &QButtonGroup::idClicked, ui->mapView, &MapView::setCurrentLayer);

	connect(ui->tilesTabWidget, &QTabWidget::currentChanged, ui->tilesTabWidget, [this](int index)
	{
		if (index == 0)
		{
			//ui->layerButton_0->setEnabled(true);
			ui->mapView->setCurrentLayer(0);
			ui->layerButton_1->setEnabled(false);
			ui->layerButton_2->setEnabled(false);
			//ui->layerButton_0->click();
		}
		else
		{
			//ui->layerButton_0->setEnabled(false);
			ui->mapView->setCurrentLayer(ui->paintLayerButtonGroup->checkedId());
			ui->layerButton_1->setEnabled(true);
			ui->layerButton_2->setEnabled(true);

			//if (ui->paintLayerButtonGroup->checkedId() == 0)
			//	ui->layerButton_1->click();
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
		QSettings settings("settings.ini", QSettings::Format::IniFormat);
		QString path = settings.value("path").toString();
		QStringList arguments { "--url", path };
		QProcess *process = new QProcess(this);
		process->start("/home/dimich/.local/RPG Maker MV/nwjs-lnx-test/Game", arguments);
	});

	connect(ui->mapView, &MapView::editEvent, [this](int eventId)
	{
		MapEventsTab *mapEventsTab = new MapEventsTab();
		mapEventsTab->resize(1280, 720);
		mapEventsTab->setWindowModality(Qt::ApplicationModal);
		mapEventsTab->init(currentMap);
		mapEventsTab->selectEvent(eventId);
		mapEventsTab->show();
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
	delete ui;
}

void MapTab::init()
{
	model = new MapInfoModel(ui->mapInfoTable);
	ui->mapInfoTable->setModel2(model);
	//ui->mapInfoTable->hideColumn(1);
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

	uint64_t end = QDateTime::currentMSecsSinceEpoch();
	emit mapLoadTime(end - start);
}

void MapTab::mapInfoTableDoubleClicked(const QModelIndex &)
{
	int id = ui->mapInfoTable->selectedId();
	currentMapId = id;
	loadMap(id);
	emit mapLoaded(currentMap);
}
