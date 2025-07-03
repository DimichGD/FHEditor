#include "change_maximum_dialog.hpp"
#include "ui_change_maximum_dialog.h"

#include <QAbstractItemModel>

ChangeMaximumDialog::ChangeMaximumDialog(QAbstractItemModel *model, QWidget *parent):
	QDialog(parent), ui(new Ui::ChangeMaximumDialog)
{
	ui->setupUi(this);
	ui->spinBox->setValue(model->rowCount());
	setMaximumSize(size());

	if (parent)
	{
		QPoint pos = parent->mapToGlobal(QPoint());
		pos.setY(pos.y() - height() - 64);
		move(pos);
	}

	/*connect(this, &QDialog::accepted, [model, this]()
	{
		int count = ui->spinBox->value() + 1;
		int rowCount = model->rowCount();

		if (count < rowCount)
			model->removeRows(count - 1, rowCount - count);

		else if (count > rowCount)
			model->insertRows(rowCount, count - rowCount);
	});*/
}

ChangeMaximumDialog::~ChangeMaximumDialog()
{
	delete ui;
}

int ChangeMaximumDialog::value() const
{
	return ui->spinBox->value();
}
