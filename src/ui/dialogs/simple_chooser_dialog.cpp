#include "simple_chooser_dialog.hpp"
#include "base_table.hpp"
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
void readModel(QStandardItemModel *model)
{
	for (auto item: Database::Get()->getStorage<T>())
	{
		if (!item)
			model->appendRow(newItem("", 0));

		else
			model->appendRow(newItem(item->name, item->id));
	}
}

void readStrings(QStandardItemModel *model, const std::vector<QString> &strings)
{
	int counter = 0;
	for (auto &item: strings)
		model->appendRow(newItem(item, counter++));
}

SimpleChooserDialog::SimpleChooserDialog(Source source, int targetId, QWidget *parent):
	QDialog(parent), ui(new Ui::SimpleChooserDialog)
{
	ui->setupUi(this);
	ui->listView->setFocus();

	model = new QStandardItemModel(ui->listView);
	model->setColumnCount(1);

	if (source == ANIMATION)
	{
		model->appendRow(newItem("Normal Attack", -1));
		model->setData(model->index(1, 0), "None", Qt::DisplayRole);
		readModel<Animation>(model);
		++targetId;
	}

	else if (source == STATE)
		readModel<State>(model);

	else if (source == SKILL)
		readModel<Skill>(model);

	else if (source == SWITCH)
		readStrings(model, Database::Get()->system()->switches);

	else if (source == VARIABLE)
		readStrings(model, Database::Get()->system()->variables);

	else if (source == SKILL)
		readModel<Skill>(model);

	else if (source == ITEM)
		readModel<Item>(model);

	else if (source == COMMON_EVENT)
		readModel<Event>(model);

	else
		return;

	if (source == ANIMATION)
		filterModel = new QSortFilterProxyModel(this);
	else
		filterModel = new ProxyModel(this);

	filterModel->setSourceModel(model);
	filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

	ui->listView->setModel(filterModel);
	ui->listView->setCurrentIndex(filterModel->mapFromSource(model->index(targetId, 0)));
	ui->listView->scrollTo(filterModel->mapFromSource(model->index(targetId, 0)));

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
