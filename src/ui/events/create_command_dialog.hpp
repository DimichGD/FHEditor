#pragma once
#include <QDialog>
#include <QModelIndex>

namespace Ui { class CreateCommandDialog; }

class CreateCommandDialog: public QDialog
{
	Q_OBJECT

public:
	explicit CreateCommandDialog(QModelIndex index, QWidget *parent = nullptr);
	~CreateCommandDialog();

protected:
	void openShowTextDialog();

private:
	Ui::CreateCommandDialog *ui;
	QModelIndex currentIndex;
};

