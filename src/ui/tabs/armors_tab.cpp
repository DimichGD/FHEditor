#include "armors_tab.hpp"
#include "ui_armors_tab.h"

ArmorsTab::ArmorsTab(QWidget *parent):
	QWidget(parent), ui(new Ui::ArmorsTab)
{
	ui->setupUi(this);
}

ArmorsTab::~ArmorsTab()
{
	delete ui;
}
