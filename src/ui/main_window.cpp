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

#include <QCloseEvent>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	resize(1280, 720);

	if (!Settings::Get()->load())
		qDebug() << "Can't load settings.";


	//qDebug().noquote() << db->system()->gameTitle;
	//qDebug().noquote() << db->system()->terms.messages["levelUp"];

	connect(ui->actionSave_Current_Tab, &QAction::triggered,
			[this](bool)
	{
		/*switch (ui->tabWidget->currentIndex())
		{
			//case 1: Database::Get()->save(Database::ITEMS); break;
			//case 2: Database::Get()->save(Database::WEAPONS); break;
			case 2: Database::Get()->save(Database::ITEMS); break;
			default: qDebug() << "Tab " << ui->tabWidget->currentIndex() << " save request";
		}*/

		const QString &tabObjectName = ui->tabWidget->currentWidget()->objectName();
		if (tabObjectName == "mapTab")
			Database::Get()->saveMap(ui->mapTab->mapId());

		else if (tabObjectName == "mapEventsTab")
			Database::Get()->saveMap(ui->mapTab->mapId());

		else if (tabObjectName == "itemsTab")
			Database::Get()->save(Database::ITEMS);

		else if (tabObjectName == "commonEventsTab")
			Database::Get()->save(Database::EVENTS);

		//qDebug() << tabObjectName;
		ui->statusBar->showMessage("Saved", 5000);
		// write to status bar
	});

	/*connect(ui->mapTab, &MapTab::mapLoadTime, [this](int msecs)
	{
		QString message = QString("Map loaded in %1 milliseconds.").arg(msecs);
		ui->statusBar->showMessage(message, 5000);
	});*/

	connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(ui->actionGamesList, &QAction::triggered, this, &MainWindow::openSettingsDialog);
	connect(ui->mapTab, &MapTab::mapLoaded, ui->mapEventsTab, &MapEventsTab::init);
	connect(ui->mapTab, &MapTab::selectMapEvent, ui->mapTab, [this](int eventId)
	{
		ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->mapEventsTab));
		ui->mapEventsTab->selectEvent(eventId);
	});

	connect(ui->itemsTab, &ItemsTab::selectCommonEvent, ui->itemsTab, [this](int eventId)
	{
		ui->tabWidget->setCurrentIndex(ui->tabWidget->indexOf(ui->commonEventsTab));
		//ui->commonEventsTab->selectEvent(eventId); // TODO: implement selectEvent
	});


	if (Settings::Get()->lastPath.isEmpty())
	{
		openSettingsDialog();
	}
	else
	{
		loadGame();
	}

	ui->tabWidget->setCurrentIndex(Settings::Get()->lastTabIndex);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::loadGame()
{
	uint64_t start = QDateTime::currentMSecsSinceEpoch();

	if (Settings::Get()->lastPath.isEmpty())
	{
		qDebug() << "lastPath is empty";
		return;
	}

	if (!Images::Get()->load())
	{
		qDebug() << "Failed to load Images";
		return;
	}

	Database::Get()->load(Database::ALL);
	/*Database::Get()->load(Database::CLASSES);
	Database::Get()->load(Database::ACTORS);
	Database::Get()->load(Database::ITEMS);
	Database::Get()->load(Database::SYSTEM);*/

	//mapEventsTab->init();
	ui->itemsTab->init();
	ui->commonEventsTab->init();
	ui->typesTab->init();
	ui->mapTab->init();
	ui->animationTab->init();

	uint64_t end = QDateTime::currentMSecsSinceEpoch();
	ui->statusBar->showMessage(QString("Database loaded in %1 msecs.").arg(end - start), 5000);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Settings::Get()->lastTabIndex = ui->tabWidget->currentIndex();
	Settings::Get()->save();
	event->accept();
}

void MainWindow::openSettingsDialog()
{
	GamesListDialog dialog(this);
	if (dialog.exec())
		loadGame();
}

