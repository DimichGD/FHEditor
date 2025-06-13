#pragma once
#include "map.hpp"
#include <QAbstractTableModel>

class MapEventsModel: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit MapEventsModel(Map *map, QObject *parent = nullptr):
		QAbstractTableModel(parent), currentMap(map) {};

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;

	//MapEvent *eventFromRow(int row);
	/*QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &child = QModelIndex()) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;*/

private:
	Map *currentMap = nullptr;
};

