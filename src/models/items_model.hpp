#pragma once
#include "base_model.hpp"
#include "item.hpp"

class ItemsModel: public BaseModel2
{
public:
	ItemsModel(QObject *parent = nullptr);

	Item *item(int row);
	std::vector<Effect> *effects(int row);

protected:
	QVariant data(int row, int column) const override;
	void setData(int row, int column, const QVariant &value) override;

private:
	Accessor<Item> accessor;
};
