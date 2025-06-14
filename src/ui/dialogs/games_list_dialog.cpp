#include "games_list_dialog.hpp"
#include "json_stuff.hpp"
//#include "rpgmmz/system_mz.hpp"
#include "system.hpp"
#include "settings.hpp"
#include "ui_games_list_dialog.h"

#include <QFileDialog>
#include <QMessageBox>

GamesListDialog::GamesListDialog(QWidget *parent): QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	for (auto &game: Settings::Get()->gamesList)
	{
		addRow(game.name, game.path);

		if (game.name == Settings::Get()->lastPath)
			ui->gameTable->selectRow(ui->gameTable->rowCount() - 1);
	}

	connect(ui->addGameButton, &QPushButton::clicked, this, &GamesListDialog::addGameClicked);
	connect(ui->removeGameButton, &QPushButton::clicked, this, &GamesListDialog::removeGameClicked);
	connect(ui->gameTable, &QTableWidget::itemDoubleClicked, this, &QDialog::accept);
	connect(this, &QDialog::accepted, this, &GamesListDialog::saveSettings);
}

GamesListDialog::~GamesListDialog()
{
	delete ui;
}



void GamesListDialog::addGameClicked()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.selectFile("System.json");
	dialog.setNameFilter("System file (System.json)");
	if (!dialog.exec())
		return;

	QString selectedFile = dialog.selectedFiles().at(0);

	System systemObject;
	if (!loadJson(selectedFile, systemObject))
	{
		QMessageBox messageBox;
		messageBox.setText("Failed to load 'System.json'\n");
		messageBox.exec();
		return;
	}

	QString name = systemObject.gameTitle;
	QString path = QDir::cleanPath(QFileInfo(selectedFile).absolutePath() + "/../");

	Settings::Get()->gamesList.append({ name, path });
	addRow(name, path);
}

void GamesListDialog::removeGameClicked()
{
	if (ui->gameTable->currentRow() < 0)
		return;

	Settings::Get()->gamesList.removeAt(ui->gameTable->currentRow());
	ui->gameTable->removeRow(ui->gameTable->currentRow());
}


void GamesListDialog::saveSettings()
{
	if (ui->gameTable->currentRow() < 0)
		return;

	QTableWidgetItem *pathItem = ui->gameTable->item(ui->gameTable->currentRow(), 1);
	Settings::Get()->lastPath = pathItem->data(Qt::DisplayRole).toString();
	Settings::Get()->save();
}

void GamesListDialog::addRow(const QString &name, const QString &path)
{
	int lastRow = ui->gameTable->rowCount();
	ui->gameTable->insertRow(lastRow);
	ui->gameTable->setItem(lastRow, 0, new QTableWidgetItem(name));
	ui->gameTable->setItem(lastRow, 1, new QTableWidgetItem(path));
	ui->gameTable->resizeColumnToContents(0);
	ui->gameTable->resizeRowsToContents();
}
