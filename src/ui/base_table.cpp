#include "base_table.hpp"
//#include "iconset.hpp"

#include <QEvent>
#include <QMouseEvent>
#include <QHeaderView>

BaseTable::BaseTable(QWidget *parent): QTableView(parent)
{
	/*QPalette pal = palette();
	pal.setColor(QPalette::Base, QColor::fromRgb(255, 255, 255));
	pal.setColor(QPalette::AlternateBase, QColor::fromRgb(228, 236, 241));
	pal.setColor(QPalette::Inactive, QPalette::Highlight,
				 pal.color(QPalette::Active, QPalette::Highlight));
	pal.setColor(QPalette::Inactive, QPalette::HighlightedText,
				 pal.color(QPalette::Active, QPalette::HighlightedText));
	setPalette(pal);

	QFont currentFont = font();
	currentFont.setPointSize(12);
	setFont(currentFont);*/

	//setItemDelegateForColumn(1, new IconDelegate(this));
	filterModel = new ProxyModel(this);
}

void BaseTable::setModel2(QAbstractItemModel *model, QPixmap *iconSetPixmap)
{
	//filterModel = new ProxyModel(this);
	filterModel->setSourceModel(model);
	filterModel->setDynamicSortFilter(true);
	filterModel->setFilterKeyColumn(model->columnCount() - 1);
	filterModel->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);

	QTableView::setModel(filterModel);
	//sortByColumn(0, Qt::SortOrder::AscendingOrder);

	resizeColumnToContents(0);
	if (model->columnCount() == 3)
		resizeColumnToContents(1);
	//resizeRowsToContents();
	//verticalHeader()->setDefaultSectionSize(40);

	connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &BaseTable::currentRowChanged);

	this->model = model;

	if (iconSetPixmap)
		setItemDelegateForColumn(1, new IconDelegate(iconSetPixmap, this));
}

int BaseTable::originalRow(int filteredRow)
{
	return filterModel->mapToSource(filterModel->index(filteredRow, 0)).row();
}

int BaseTable::rowCount()
{
	return filterModel->rowCount();
}

void BaseTable::setFilterText(const QString &text)
{
	filterModel->setFilterFixedString(text);
}

void BaseTable::selectRow(int row)
{
	//QModelIndex index = filterModel->mapFromSource(model->index(row, 0));
	/*QModelIndex index = filterModel->mapToSource(filterModel->index(row, 0));
	if (!index.isValid())
		return;*/

	//QTableView::selectRow(index.row());
	QTableView::selectRow(row);
}

void BaseTable::currentRowChanged(const QModelIndex &selected, const QModelIndex &)
{
	currentRow = originalRow(selected.row());
	emit rowSelected(currentRow);
}

void BaseTable::mousePressEvent(QMouseEvent *event)
{
	if (!indexAt(event->position().toPoint()).isValid())
	{
		event->accept();
		return;
	}

	QTableView::mousePressEvent(event);
}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	if (source_row == 0)
		return false;

	if (customFilter)
		if (sourceModel()->data(sourceModel()->index(source_row, customFilterColumn), Qt::EditRole) != customFilterValue)
			return false;

	return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

void ProxyModel::setFilterEditRole(int column, QVariant filter)
{
	// beginFilterChange(); TODO: Since Qt 6.9
	customFilter = true;
	customFilterColumn = column;
	customFilterValue = filter;
	invalidateFilter();
}

void ProxyModel::disableCustomFilter()
{
	// beginFilterChange(); TODO: Since Qt 6.9
	customFilter = false;
	invalidateFilter();
}
