#pragma once
#include "map_event.hpp"
#include <QAbstractTableModel>

class MapEventPagesModel: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit MapEventPagesModel(QObject *parent):
		QAbstractTableModel(parent) {}

	Page *page(int index) { return &pages->at(index); }
	void setPages(std::vector<Page> *pages);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
	std::vector<Page> *pages = nullptr;
};

