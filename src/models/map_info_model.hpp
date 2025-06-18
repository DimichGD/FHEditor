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

private:
	Accessor<MapInfo> accessor;
};
