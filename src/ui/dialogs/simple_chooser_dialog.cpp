#include "simple_chooser_dialog.hpp"
#include "database.hpp"
#include "ui_simple_chooser_dialog.h"

#include <QListView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

QStandardItem *newItem(QString name, int id)
{
	QStandardItem *item = new QStandardItem(name);
	item->setData(id, Qt::UserRole);
	return item;
}

template<typename T>
int readModel(QStandardItemModel *model, int targetId)
{
	int currentRow = 0;
	int counter = 0;
	for (auto item: Database::Get()->getVector<T>())
	{
		if (item)
		{
			model->appendRow(newItem(item->name, item->id));
			if (item->id == targetId)
				currentRow = counter;

			++counter;
		}
	}

	return currentRow;
}

int readStrings(QStandardItemModel *model, const std::vector<std::string> &strings, int targetId)
{
	int currentRow = 0;
	int counter = 0;
	for (auto &item: strings)
	{
		model->appendRow(newItem(QString::fromStdString(item), counter));
		if (counter == targetId)
			currentRow = counter;

		++counter;
	}

	return currentRow;
}

SimpleChooserDialog::SimpleChooserDialog(Source source, int targetId, QWidget *parent):
	QDialog(parent), ui(new Ui::SimpleChooserDialog)
{
	ui->setupUi(this);
	ui->listView->setFocus();

	model = new QStandardItemModel(ui->listView);
	model->setColumnCount(1);

	int currentRow = 0;
	if (source == ANIMATION)
		currentRow = readModel<Animation>(model, targetId);

	else if (source == STATE)
		currentRow = readModel<State>(model, targetId);

	else if (source == SKILL)
		currentRow = readModel<Skill>(model, targetId);

	else if (source == SWITCH) // TODO: again, get from copy
	{
		currentRow = readStrings(model, Database::Get()->system()->switches, targetId);
		ui->listView->setRowHidden(0, true);
	}

	else if (source == VARIABLE) // TODO: again, get from copy
	{
		currentRow = readStrings(model, Database::Get()->system()->variables, targetId);
		ui->listView->setRowHidden(0, true);
	}

	else if (source == SKILL)
		currentRow = readModel<Skill>(model, targetId);

	else if (source == ITEM)
		currentRow = readModel<Item>(model, targetId);

	else if (source == COMMON_EVENT)
		currentRow = readModel<Event>(model, targetId);

	else
		return;

	filterModel = new QSortFilterProxyModel(this);
	filterModel->setSourceModel(model);
	filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	ui->listView->setModel(filterModel);
	ui->listView->setCurrentIndex(filterModel->index(currentRow, 0));
	ui->listView->scrollTo(filterModel->index(currentRow, 0));

	connect(ui->filterEdit, &QLineEdit::textChanged,
			filterModel, &QSortFilterProxyModel::setFilterFixedString);
}

SimpleChooserDialog::~SimpleChooserDialog()
{
	delete ui;
}

int SimpleChooserDialog::result()
{
	return ui->listView->currentIndex().data(Qt::UserRole).toInt();
}
