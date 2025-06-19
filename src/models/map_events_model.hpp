#pragma once
#include "base_model.hpp"
#include "map.hpp"
#include <QAbstractTableModel>

class MapEventsModel: public BaseModel
{
	Q_OBJECT

public:
	explicit MapEventsModel(Map *map, QObject *parent = nullptr)
		: BaseModel(&accessor, 2, parent), accessor(&map->events)
	{
		//accessor = Accessor<MapEvent>(&map->events);
	}
		//QAbstractTableModel(parent), currentMap(map) {};

protected:
	QVariant dataForDisplay(int row, int column) const override
	{
		const MapEvent *event = accessor.value(row);
		if (!event)
			return QVariant();

		if (column == 0) return event->id;
		if (column == 1) return event->name;

		return QVariant();
	}

	/*int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;*/

	//MapEvent *eventFromRow(int row);
	/*QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &child = QModelIndex()) const override;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role) const override;*/

private:
	Map *currentMap = nullptr;
	Accessor<MapEvent> accessor;

	// BaseModel interface
};

