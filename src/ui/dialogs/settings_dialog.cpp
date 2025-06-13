#include "settings_dialog.hpp"
#include "json_stuff.hpp"
#include "rpgmmz/system_mz.hpp"
#include "system.hpp"
#include "ui_settings_dialog.h"

#include <QRadioButton>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent): QDialog(parent), ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);

	QSettings settings("settings.ini", QSettings::Format::IniFormat);
	QString defaultPath = settings.value("path").toString();
	settings.beginGroup("Games");
	int arrayLength = settings.beginReadArray("game");

	for (int i = 0; i < arrayLength; i++)
	{
		settings.setArrayIndex(i);
		QString name = settings.value("name").toString();
		QString path = settings.value("path").toString();

		addRow(name, path);

		if (defaultPath == path)
			ui->gameTable->selectRow(ui->gameTable->rowCount() - 1);
	}

	settings.endArray();
	settings.endGroup();

	connect(ui->addGameButton, &QPushButton::clicked, this, &SettingsDialog::addGameClicked);
	connect(ui->removeGameButton, &QPushButton::clicked, this, &SettingsDialog::removeGameClicked);
	connect(ui->gameTable, &QTableWidget::itemDoubleClicked, this, &QDialog::accept);
	connect(this, &QDialog::accepted, this, &SettingsDialog::saveSettings);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}



void SettingsDialog::addGameClicked()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.selectFile("System.json");
	dialog.setNameFilter("System file (System.json)");
	if (!dialog.exec())
		return;

	System systemObject;
	if (!loadJson(dialog.selectedFiles()[0], systemObject))
	{
		MZ::System systemMZObject;
		if (!loadJson(dialog.selectedFiles()[0], systemMZObject))
		{
			QMessageBox messageBox;
			messageBox.setText("Failed to load 'System.json'\n");
			messageBox.exec();
			return;
		}
	}

	QString name = QString::fromStdString(systemObject.gameTitle);
	QString path = QDir::cleanPath(QFileInfo(dialog.selectedFiles()[0]).absolutePath() + "/../");

	addRow(name, path);
}

void SettingsDialog::removeGameClicked()
{
	if (ui->gameTable->currentRow() < 0)
		return;

	ui->gameTable->removeRow(ui->gameTable->currentRow());
}


void SettingsDialog::saveSettings()
{
	QSettings settings("settings.ini", QSettings::Format::IniFormat);

	settings.beginGroup("Games");
	settings.beginWriteArray("game");
	for (int i = 0; i < ui->gameTable->rowCount(); i++)
	{
		QTableWidgetItem *nameItem = ui->gameTable->item(i, 0);
		QTableWidgetItem *pathItem = ui->gameTable->item(i, 1);

		settings.setArrayIndex(i);
		settings.setValue("name", nameItem->data(Qt::DisplayRole));
		settings.setValue("path", pathItem->data(Qt::DisplayRole));
	}
	settings.endArray();
	settings.endGroup();

	QTableWidgetItem *pathItem = ui->gameTable->item(ui->gameTable->currentRow(), 1);
	QString currentPath = pathItem->data(Qt::DisplayRole).toString();
	settings.setValue("path", currentPath);
	settings.sync();
}

void SettingsDialog::addRow(const QString &name, const QString &path)
{
	int lastRow = ui->gameTable->rowCount();
	ui->gameTable->insertRow(lastRow);
	ui->gameTable->setItem(lastRow, 0, new QTableWidgetItem(name));
	ui->gameTable->setItem(lastRow, 1, new QTableWidgetItem(path));
	ui->gameTable->resizeColumnToContents(0);
	ui->gameTable->resizeRowsToContents();
}
