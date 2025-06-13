#pragma once
#include "event.hpp"
#include <QAbstractTableModel>

class MapEventPagesModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	explicit MapEventPagesModel(std::vector<Page> *pages, QObject *parent):
		QAbstractTableModel(parent) { this->pages = pages; }

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
	std::vector<Page> *pages = nullptr;
};

