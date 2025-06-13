#pragma once
#include <QDialog>

namespace Ui { class ChangeMaximumDialog; }
class QAbstractItemModel;

class ChangeMaximumDialog: public QDialog
{
	Q_OBJECT

public:
	explicit ChangeMaximumDialog(QAbstractItemModel *model, QWidget *parent = nullptr);
	~ChangeMaximumDialog();

	int value() const;

private:
	Ui::ChangeMaximumDialog *ui = nullptr;
};

