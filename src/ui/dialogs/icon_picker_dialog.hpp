#pragma once
#include "directory_list_view.hpp"
#include "ui_icon_picker_dialog.h"

class IconPickerDialog: public QDialog
{
	Q_OBJECT

public:
	IconPickerDialog(QWidget *parent, PickerType type, QString filename, int iconIndex);
	~IconPickerDialog();

	int index() { return ui->graphicsView->index; }
	QString name() { return itemName; }

protected:
	void setupGraphicsView(int x, int y, QPixmap *pixmap, int tileSize);
	void listViewClicked(const QModelIndex &index);

private:
	PickerType type;
	QString itemName {};
	Ui::IconPickerDialog *ui = nullptr;
};

