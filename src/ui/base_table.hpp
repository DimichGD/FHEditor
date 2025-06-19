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
};


class IconDelegate: public QStyledItemDelegate
{
public:
	IconDelegate(QPixmap *iconSetPixmap, QObject * parent)
		: QStyledItemDelegate(parent), pixmap(iconSetPixmap) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		int iconIndex = index.data(Qt::DecorationRole).toInt();
		int y = iconIndex / 16; // TODO: Check boundaries
		int x = iconIndex % 16;

		QRect rect(0, 0, 32, 32);
		rect.setX(option.rect.x() + (option.rect.width() - 32) / 2);
		rect.setY(option.rect.y() + (option.rect.height() - 32) / 2);
		//rect.setWidth(32);
		//rect.setHeight(32);
		painter->drawPixmap(rect, *pixmap, { x * 32, y * 32, 32, 32 });
	}

private:
	QPixmap *pixmap = nullptr;
};


class BaseTable: public QTableView
{
	Q_OBJECT

public:
	BaseTable(QWidget *parent = nullptr);

	//int selectedId() const { return currentId; }
	int selectedRow() const { return currentRow; }
	int originalRow(int filteredRow); // TODO: move this to private?
	//int rowCount();

	//void addRow(int id, std::string name, int iconIndex);
	//void updateRow(int rowIndex, QString name, int iconIndex = -1);
	//void removeRows(int rowIndex, int count);
	void setModel2(QAbstractItemModel *model, QPixmap *iconSetPixmap = nullptr);

public slots:
	void setFilterText(const QString &text);
	void selectRow(int row);

protected:
	QSortFilterProxyModel *filterModel = nullptr;
	QAbstractItemModel *model = nullptr;
	int currentRow = -1;
	//int currentId = -1;

	void onSelectionChanged(const QModelIndex &selected, const QModelIndex &);

signals:
	void rowSelected(int row);
};
