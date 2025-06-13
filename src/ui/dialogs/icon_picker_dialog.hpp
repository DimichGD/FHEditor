#pragma once
#include "ui_icon_picker_dialog.h"

class IconPickerDialog: public QDialog
{
	Q_OBJECT

public:
	IconPickerDialog(QWidget *parent, int icon_index);
	~IconPickerDialog();

	int index() { return ui->graphicsView->index; }

private:
	//IconPickerView *scene = nullptr;
	Ui::IconPickerDialog *ui = nullptr;
};

