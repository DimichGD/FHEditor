#pragma once
#include "base_model.hpp"

class MapInfoModel: public BaseModel
{
	Q_OBJECT
public:
	explicit MapInfoModel(QObject *parent = nullptr): BaseModel(&accessor, 2, parent) {}
	MapInfo *mapInfo(int row);

protected:
	QVariant displayRoleData(int row, int column, Triple pointer) const override;
	QVariant editRoleData(int row, int column, Triple pointer) const override;
	void setEditRoleData(int row, int column, const QVariant &value, Triple pointer) override;

private:
	Accessor<MapInfo> accessor;
};
