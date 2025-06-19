#include "main_window.hpp"

#include "animations_tab.hpp"
#include "map_tab.hpp"
#include "map_events_tab.hpp"
#include "items_tab.hpp"
#include "armors_tab.hpp"
#include "weapons_tab.hpp"
#include "common_events_tab.hpp"
#include "types_tab.hpp"

#include "database.hpp"
#include "images.hpp"
//#include "iconset.hpp"
#include "settings.hpp"

#include "games_list_dialog.hpp"
#include "ui_main_window.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	resize(1280, 720);

	if (!Settings::Get()->load())
		qDebug() << "Can't load settings.";


	mapTab = new MapTab(this);
	mapEventsTab = new MapEventsTab(this);
	itemsTab = new ItemsTab(this);
	weaponsTab = new WeaponsTab(this);
	armorsTab = new ArmorsTab(this);
	commonEventsTab = new CommonEventsTab(this);
	typesTab = new TypesTab(this);
	animationTab = new AnimationsTab(this);

	//qDebug().noquote() << db->system()->gameTitle;
	//qDebug().noquote() << db->system()->terms.messages["levelUp"];

	connect(ui->actionSave_Current_Tab, &QAction::triggered,
			[this](bool)
	{
		switch (ui->tabWidget->currentIndex())
		{
			//case 1: Database::Get()->save(Database::ITEMS); break;
			//case 2: Database::Get()->save(Database::WEAPONS); break;
			case 2: Database::Get()->save(Database::ITEMS); break;
			default: qDebug() << "Tab " << ui->tabWidget->currentIndex() << " save request";
		}

		// write to status bar
	});

	connect(mapTab, &MapTab::mapLoadTime, [this](int msecs)
	{
		QString message = QString("Map loaded in %1 milliseconds.").arg(msecs);
		ui->statusBar->showMessage(message, 5000);
	});

	mapTabIndex = ui->tabWidget->addTab(mapTab, "Map");
	mapEventsTabIndex = ui->tabWidget->addTab(mapEventsTab, "Map Events");
	itemsTabIndex = ui->tabWidget->addTab(itemsTab, "Items");
	weaponsTabIndex = ui->tabWidget->addTab(weaponsTab, "Weapons");
	armorsTabIndex = ui->tabWidget->addTab(armorsTab, "Armors");
	commonEventsTabIndex = ui->tabWidget->addTab(commonEventsTab, "Common Events");
	typesTabIndex = ui->tabWidget->addTab(typesTab, "Types");
	animationTabIndex = ui->tabWidget->addTab(animationTab, "Animations");
	ui->tabWidget->setCurrentIndex(commonEventsTabIndex);

	connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(ui->actionGamesList, &QAction::triggered, this, &MainWindow::openSettingsDialog);
	connect(mapTab, &MapTab::mapLoaded, mapEventsTab, &MapEventsTab::init);
	connect(mapTab, &MapTab::editMapEvent, mapTab, [this](int eventId)
	{
		ui->tabWidget->setCurrentIndex(mapEventsTabIndex);
		mapEventsTab->selectEvent(eventId);
	});

	if (Settings::Get()->lastPath.isEmpty())
	{
		openSettingsDialog();
	}
	else
	{
		loadGame();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadGame()
{
	if (Settings::Get()->lastPath.isEmpty())
	{
		qDebug() << "lastPath is empty";
		return;
	}

	if (!Images::Get()->load())
		qDebug() << "Failed to load Images";

	uint64_t start = QDateTime::currentMSecsSinceEpoch();

	Database::Get()->load(Database::ALL);

	//mapEventsTab->init();
	itemsTab->init();
	commonEventsTab->init();
	typesTab->init();
	mapTab->init();
	animationTab->init();

	uint64_t end = QDateTime::currentMSecsSinceEpoch();
	ui->statusBar->showMessage(QString("Database loaded in %1 msecs.").arg(end - start), 5000);
}

void MainWindow::openSettingsDialog()
{
	GamesListDialog dialog(this);
	if (dialog.exec())
		loadGame();
}

