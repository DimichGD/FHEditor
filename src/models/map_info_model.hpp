#pragma once
#include "base_model.hpp"

class MapInfoModel : public BaseModel
{
	Q_OBJECT
public:
	explicit MapInfoModel(QObject *parent = nullptr): BaseModel(&accessor, 2, parent) {}
	MapInfo *mapInfo(int row);

protected:
	QVariant dataForDisplay(int row, int column) const override;
	QVariant iconForDisplay(int row, int column) const override;
	QVariant dataForMapper(int row, int column) const override { return QVariant(); };
	void setDataFromMapper(int row, int column, const QVariant &value) override {};

private:
	Accessor<MapInfo> accessor;
};
