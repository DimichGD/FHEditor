#pragma once
#include "base_model.hpp"
#include "event.hpp"

class CommonEventsModel: public BaseModel2
{
public:
	CommonEventsModel(QObject *parent = nullptr);
	Event *commonEvent(int row);

protected:
	QVariant data(int id, int column) const override;
	void setData(int id, int column, const QVariant &value) override;

private:
	Accessor<Event> accessor;
};

