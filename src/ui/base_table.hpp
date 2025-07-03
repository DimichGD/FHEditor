#pragma once

#include <QString>
#include <QTableView>
#include <QPainter>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QSortFilterProxyModel>

class ProxyModel: public QSortFilterProxyModel
{
	Q_OBJECT

public:
	ProxyModel(QObject *parent = nullptr): QSortFilterProxyModel(parent) {}
	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
	void setFilterEditRole(int column, QVariant filter);
	void disableCustomFilter();

private:
	//bool skipZeroIndex = true;
	bool customFilter = false;
	int customFilterColumn = 0;
	QVariant customFilterValue {};
};


class IconDelegate: public QStyledItemDelegate
{
public:
	IconDelegate(QPixmap *iconSetPixmap, QObject * parent)
		: QStyledItemDelegate(parent), pixmap(iconSetPixmap) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		//int iconIndex = index.data(Qt::DecorationRole).toInt();
		int iconIndex = index.data(Qt::DisplayRole).toInt();
		int y = iconIndex / 16; // TODO: Check boundaries
		int x = iconIndex % 16;

		QRect rect(0, 0, 32, 32);
		rect.setX(option.rect.x() + (option.rect.width() - 32) / 2);
		rect.setY(option.rect.y() + (option.rect.height() - 32) / 2);
		//rect.setWidth(32);
		//rect.setHeight(32);
		painter->drawPixmap(rect, *pixmap, { x * 32, y * 32, 32, 32 });
	}

	/*QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
	{
		return QSize(40, 40);
	}*/

private:
	QPixmap *pixmap = nullptr;
};


class BaseTable: public QTableView
{
	Q_OBJECT

public:
	BaseTable(QWidget *parent = nullptr);

	//int selectedId() const { return currentId; }
	// TODO: Change name to selectedId or something
	int selectedRow() const { return currentRow; }
	int originalRow(int filteredRow); // TODO: move this to private?
	int rowCount();

	void setModel2(QAbstractItemModel *model, int nameColumn);

	void setCustomFilter(int column, QVariant filter)
		{ filterModel->setFilterEditRole(column, filter); }
	void disableCustomFilter()
		{ filterModel->disableCustomFilter(); }

public slots:
	void setFilterText(const QString &text);
	void selectRow(int row);

protected:
	void currentRowChanged(const QModelIndex &selected, const QModelIndex &);
	void mousePressEvent(QMouseEvent *event) override;

signals:
	void rowSelected(int row);

private:
	ProxyModel *filterModel = nullptr;
	QAbstractItemModel *model = nullptr;
	int currentRow = -1;
};
