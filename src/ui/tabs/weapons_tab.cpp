#include "weapons_tab.hpp"
#include "ui_weapons_tab.h"

WeaponsTab::WeaponsTab(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::WeaponsTab)
{
	ui->setupUi(this);
}

WeaponsTab::~WeaponsTab()
{
	delete ui;
}
