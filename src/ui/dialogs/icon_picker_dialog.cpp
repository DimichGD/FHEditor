#include "icon_picker_dialog.hpp"
#include "images.hpp"

#include <QGraphicsPixmapItem>
//#include <QStandardItemModel>
//#include <QDir>

struct PickerInfo
{
	QPixmap *pixmap = nullptr;
	int stride = 1;
	int tileSize = 1;
};

PickerInfo pickerInfo(PickerType type, QString filename)
{
	switch (type)
	{
		case ICON_SET: return { Images::Get()->iconSet(), 16, 32 };
		case FACE:  return { Images::Get()->face(filename), 4, 144 };
		default:
			qDebug() << "IconPickerDialog type is not implemented"; return {};
	}
}

IconPickerDialog::IconPickerDialog(QWidget *parent, PickerType type, QString filename, int iconIndex)
	: QDialog(parent)
{
	ui = new Ui::IconPickerDialog();
	ui->setupUi(this);
	this->type = type;

	ui->listView->setMode(type, filename);

	PickerInfo info = pickerInfo(type, filename);

	int y = iconIndex / info.stride;
	int x = iconIndex % info.stride;
	setupGraphicsView(x, y, info.pixmap, info.tileSize);

	if (type == ICON_SET)
		resize(info.pixmap->width() + 64, info.pixmap->height() + 64);

	connect(ui->listView, &DirectoryListView::clicked, this, &IconPickerDialog::listViewClicked);
}

IconPickerDialog::~IconPickerDialog()
{
	delete ui;
}

void IconPickerDialog::setupGraphicsView(int x, int y, QPixmap *pixmap, int tileSize)
{
	ui->graphicsView->setPixmap(pixmap, tileSize);
	ui->graphicsView->setPos(x, y);
}

void IconPickerDialog::listViewClicked(const QModelIndex &index)
{
	if (!index.isValid() || index.row() == 0)
	{
		itemName.clear();
		ui->graphicsView->clear();
		ui->graphicsView->setPos(0, 0);
	}
	else
	{
		itemName = index.data().toString();
		PickerInfo info = pickerInfo(type, itemName);
		setupGraphicsView(0, 0, info.pixmap, info.tileSize);
	}
}
