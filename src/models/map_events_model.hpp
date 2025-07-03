#pragma once
#include "base_model.hpp"
#include "map_event.hpp"

class MapEventsModel: public BaseModel2
{
public:
	MapEventsModel(QObject *parent = nullptr);

	MapEvent *mapEvent(int row);
	void setEvents(std::vector<std::optional<MapEvent>> *events);

protected:
	QVariant data(int row, int column) const override;
	void setData(int row, int column, const QVariant &value) override;

private:
	Accessor<MapEvent> accessor;
};

