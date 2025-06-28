#pragma once
#include "base_model.hpp"
#include "map.hpp"
#include <QAbstractTableModel>

class MapEventsModel: public BaseModel
{
	Q_OBJECT

public:
	explicit MapEventsModel(std::vector<std::optional<MapEvent>> *events, QObject *parent = nullptr)
		: BaseModel(&accessor, 2, parent), accessor(events)
	{
	}

protected:
	QVariant displayRoleData(int row, int column, Triple pointer) const override;
	QVariant editRoleData(int row, int column, Triple pointer) const override;
	QVariant userRoleData(int row, int column, Triple pointer) const override;
	void setEditRoleData(int row, int column, const QVariant &value, Triple pointer) override;

private:
	Map *currentMap = nullptr;
	Accessor<MapEvent> accessor;
};

