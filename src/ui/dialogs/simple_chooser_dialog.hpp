#pragma once
#include <QDialog>

namespace Ui { class SimpleChooserDialog; }

class QStandardItem;
class QStandardItemModel;
class QSortFilterProxyModel;


class SimpleChooserDialog: public QDialog
{
	Q_OBJECT

public:
	enum Source
	{
		ANIMATION,
		STATE,
		SKILL,
		SWITCH,
		VARIABLE,
		ITEM,
		COMMON_EVENT,
	};

	SimpleChooserDialog(Source source, int targetId, QWidget *parent);
	~SimpleChooserDialog();
	int result();

private:
	Ui::SimpleChooserDialog *ui;
	QStandardItemModel *model = nullptr;
	QSortFilterProxyModel *filterModel = nullptr;
};

