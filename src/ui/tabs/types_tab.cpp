#include "types_tab.hpp"
#include "database.hpp"
#include "ui_types_tab.h"

#include <QHeaderView>

TypesTab::TypesTab(QWidget *parent):
	QWidget(parent), ui(new Ui::TypesTab)
{
	ui->setupUi(this);

	QFont currentFont = font();
	currentFont.setPointSize(12);
	ui->elementsTableWidget->setFont(currentFont);
	ui->skillTypeTableWidget->setFont(currentFont);
	ui->weaponTypeTableWidget->setFont(currentFont);
	ui->armorTypeTableWidget->setFont(currentFont);
	ui->equipmentTypeTableWidget->setFont(currentFont);
}

TypesTab::~TypesTab()
{
	delete ui;
}

void TypesTab::init()
{
	fillTable(ui->elementsTableWidget, Database::Get()->system()->elements);
	fillTable(ui->skillTypeTableWidget, Database::Get()->system()->skillTypes);
	fillTable(ui->weaponTypeTableWidget, Database::Get()->system()->weaponTypes);
	fillTable(ui->armorTypeTableWidget, Database::Get()->system()->armorTypes);
	fillTable(ui->equipmentTypeTableWidget, Database::Get()->system()->equipTypes);
}

void TypesTab::fillTable(QTableWidget *widget, std::vector<std::string> &strings)
{
	widget->setRowCount(0);

	for (auto &string: strings)
	{
		int lastRow = widget->rowCount();
		widget->insertRow(lastRow);

		QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(lastRow));
		QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(string));

		idItem->setData(Qt::UserRole, lastRow);
		idItem->setFlags(idItem->flags() & ~(Qt::ItemIsEditable));
		nameItem->setData(Qt::UserRole, lastRow);

		widget->setItem(lastRow, 0, idItem);
		widget->setItem(lastRow, 1, nameItem);
	}

	widget->resizeColumnToContents(0);
	widget->hideRow(0);
}
