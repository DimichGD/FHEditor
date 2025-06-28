#include "icon_widget.hpp"
#include "icon_picker_dialog.hpp"
#include "images.hpp"
#include "ui_icon_widget.h"

IconWidget::IconWidget(QWidget *parent) :QWidget(parent), ui(new Ui::IconWidget)
{
	ui->setupUi(this);
	ui->iconLabel->setIconMode(ClickableLabel::Mode::ICON_SET, Images::Get()->iconSet());

	connect(ui->iconLabel, &ClickableLabel::doubleClicked, this, &IconWidget::openPickerDialog);
}

IconWidget::~IconWidget()
{
	delete ui;
}

void IconWidget::setIconIndex(int iconIndex)
{
	index = iconIndex;
	ui->iconIndexLabel->setText(QString::number(index));
	ui->iconLabel->setIconIndex(index);
	emit iconChanged(index);
}

void IconWidget::openPickerDialog()
{
	IconPickerDialog dialog(this, PickerType::ICON_SET, "", index);
	if (dialog.exec())
		setIconIndex(dialog.index());
}
