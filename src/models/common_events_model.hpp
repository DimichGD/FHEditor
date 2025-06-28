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
	QVariant displayRoleData(int row, int column, Triple) const override;
	QVariant editRoleData(int row, int column, Triple) const override;
	void setEditRoleData(int row, int column, const QVariant &value, Triple) override;

private:
	Accessor<Event> accessor;
};

