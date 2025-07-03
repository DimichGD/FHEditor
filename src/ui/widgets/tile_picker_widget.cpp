#include "tile_picker_widget.hpp"
#include "ui_tile_picker_widget.h"
#include "database.hpp"
#include "images.hpp"

TilePickerWidget::TilePickerWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::TilePickerWidget)
{
	ui->setupUi(this);

	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_A, 0);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_B, 1);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_C, 2);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_D, 3);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_E, 4);
	ui->tilePickerButtonGroup->setId(ui->tilePickerButton_R, 5);

	connect(ui->tilePickerButtonGroup, &QButtonGroup::idClicked, this, &TilePickerWidget::setCurrentIndex);
}

TilePickerWidget::~TilePickerWidget()
{
	delete ui;
}

void TilePickerWidget::setTileSet(int id)
{
	TileSet *tileSet = Database::Get()->accessor<TileSet>().value(id);
	if (!tileSet)
	{
		qDebug() << "TODO: reset widget";
		return;
	}

	// TODO: load autotiles here

	for (size_t i = 4; i < tileSet->tilesetNames.size(); i++)
	{
		QString tileSetName = tileSet->tilesetNames.at(i);

		ui->tilePickerButtonGroup->button(i - 4)->setVisible(!tileSetName.isEmpty());
		pixmaps.at(i - 4) = Images::Get()->tileSet(tileSetName);
	}

	pixmaps.back() = QPixmap(":/color-grid.png");

	setCurrentIndex(0);
}

void TilePickerWidget::setCurrentIndex(int index)
{
	ui->tilePickerView->setBackgroundPixmap(TileSet::Set(index + 4), 48, pixmaps.at(index));

}
