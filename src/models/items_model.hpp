#pragma once
#include "base_model.hpp"

class ItemsModel: public BaseModel
{
public:
	ItemsModel(QObject *parent): BaseModel(&accessor, 3, parent) {}

	Item *item(int row);
	QVariant displayRoleData(int row, int column, Triple pointer) const override;
	QVariant editRoleData(int row, int column, Triple pointer) const override;
	QVariant userRoleData(int row, int column, Triple pointer) const override;
	void setEditRoleData(int row, int column, const QVariant &value, Triple pointer) override;

	QVariant effectsData(const Item *item, int row, int column) const;
	void addEffect(int itemIndex);
	void setEffect(int itemIndex, int effectIndex, Effect &&effect);
	void removeEffect(int itemIndex, int effectIndex);

private:
	Accessor<Item> accessor;
};
