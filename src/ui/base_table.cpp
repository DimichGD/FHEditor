#include "base_table.hpp"
#include "database.hpp"
#include "iconset.hpp"

#include <QFile>
#include <QHeaderView>

BaseTable::BaseTable(QWidget *parent): QTableView(parent)
{
	QPalette pal = palette();
	pal.setColor(QPalette::Base, QColor::fromRgb(255, 255, 255));
	pal.setColor(QPalette::AlternateBase, QColor::fromRgb(228, 236, 241));
	pal.setColor(QPalette::Inactive, QPalette::Highlight,
				 pal.color(QPalette::Active, QPalette::Highlight));
	pal.setColor(QPalette::Inactive, QPalette::HighlightedText,
				 pal.color(QPalette::Active, QPalette::HighlightedText));
	setPalette(pal);

	QFont currentFont = font();
	currentFont.setPointSize(12);
	setFont(currentFont);

	//setItemDelegateForColumn(1, new IconDelegate(this));
}

/*void BaseTable::addRow(int id, std::string name, int iconIndex)
{
	Database::Get()->addRow(model, id, name, iconIndex);
}

void BaseTable::updateRow(int rowIndex, QString name, int iconIndex)
{
	if (iconIndex == -1)
	{
		model->item(rowIndex, 1)->setData(name, Qt::DisplayRole);
	}
	else
	{
		model->item(rowIndex, 1)->setData(IconSet::Get()->get(iconIndex), Qt::DecorationRole);
		model->item(rowIndex, 2)->setData(name, Qt::DisplayRole);
	}
}

void BaseTable::removeRows(int rowIndex, int count)
{
	model->removeRows(rowIndex, count);
}*/

void BaseTable::setModel2(QAbstractItemModel *model)
{
	filterModel = new ProxyModel(this);
	filterModel->setSourceModel(model);
	filterModel->setFilterKeyColumn(model->columnCount() - 1);
	filterModel->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);

	QTableView::setModel(filterModel);
	//sortByColumn(0, Qt::SortOrder::AscendingOrder);

	resizeColumnsToContents();
	//resizeRowsToContents();
	//verticalHeader()->setDefaultSectionSize(40);

	connect(selectionModel(), &QItemSelectionModel::currentChanged,
		this, &BaseTable::onSelectionChanged);

	this->model = model;
}

int BaseTable::originalRow(int filteredRow)
{
	return filterModel->mapToSource(filterModel->index(filteredRow, 0)).row();
}

/*int BaseTable::rowCount()
{
	return model->rowCount();
}*/

void BaseTable::setFilterText(const QString &text)
{
	filterModel->setFilterFixedString(text);
}

void BaseTable::selectRow(int row)
{
	QTableView::selectRow(filterModel->mapFromSource(model->index(row, 0)).row());
}

void BaseTable::onSelectionChanged(const QModelIndex &selected, const QModelIndex &)
{
	currentRow = originalRow(selected.row());
	currentId = (currentRow == -1) ? -1 : selected.siblingAtColumn(0).data().toInt();

	emit rowSelected(currentRow, currentId);
}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	if (source_row == 0)
		return false;

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
