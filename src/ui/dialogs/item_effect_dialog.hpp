#pragma once
#include "effect.hpp"
#include <QDialog>

class Ui_ItemEffectDialog;
class QDataWidgetMapper;
class QStandardItemModel;

class ItemEffectDialog: public QDialog
{
	Q_OBJECT

public:
	explicit ItemEffectDialog(Effect effect, QWidget *parent = nullptr);
	~ItemEffectDialog();

	Effect value();

public slots:
	void radioButtonToggled(int index, bool toggled);

protected:
	void setModelRow(int index, int code, int dataId, int value1, int value2);

private:
	QDataWidgetMapper *mappers[13];
	QStandardItemModel *models[13];
	Ui_ItemEffectDialog *ui = nullptr;
};

