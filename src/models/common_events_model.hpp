#pragma once
#include "base_model.hpp"
#include "database.hpp"

class CommonEventsModel: public BaseModel
{
	Q_OBJECT

public:
	explicit CommonEventsModel(QObject *parent = nullptr): BaseModel(&accessor, 2, parent) {};
	Event *eventFromRow(int row);

protected:
	QVariant dataForDisplay(int row, int column) const override;
	QVariant iconForDisplay(int row, int column) const override;
	QVariant dataForMapper(int row, int column) const override;
	void setDataFromMapper(int row, int column, const QVariant &value) override;

private:
	Accessor<Event> accessor;
};

