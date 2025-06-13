#pragma once
#include "base_model.hpp"

class ItemsModel: public BaseModel
{
	Q_OBJECT

public:
	explicit ItemsModel(QObject *parent = nullptr): BaseModel(&accessor, 3, parent) {};
	Item *item(int row);

protected:
	QVariant dataForDisplay(int row, int column) const override;
	QVariant iconForDisplay(int row, int column) const override;
	QVariant dataForMapper(int row, int column) const override;
	void setDataFromMapper(int row, int column, const QVariant &value) override;

private:
	Accessor<Item> accessor;
};

