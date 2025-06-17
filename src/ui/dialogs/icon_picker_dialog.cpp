#include "icon_picker_dialog.hpp"
#include "images.hpp"
//#include "iconset.hpp"

#include <QGraphicsPixmapItem>

IconPickerDialog::IconPickerDialog(QWidget *parent, int icon_index): QDialog(parent)
{
	ui = new Ui::IconPickerDialog();
	ui->setupUi(this);
	ui->graphicsView->setTileSize(32);
	ui->graphicsView->setPixmap(Images::Get()->iconSet());

	int y = icon_index / 16;
	int x = icon_index % 16;
	ui->graphicsView->setPos(x, y);

	QPixmap &pixmap = Images::Get()->iconSet();
	resize(pixmap.width() + 64, pixmap.height() + 64);
	//ui->graphicsView->fitInView2();
}

IconPickerDialog::~IconPickerDialog()
{
	//delete cursor;
	delete ui;
}
