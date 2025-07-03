#pragma once
#include "base_model.hpp"
#include "map_info.hpp"

class MapInfoModel: public BaseModel2
{
public:
	MapInfoModel(QObject *parent = nullptr);
	MapInfo *mapInfo(int row);

protected:
	QVariant data(int row, int column) const override;
	void setData(int row, int column, const QVariant &value) override;

private:
	Accessor<MapInfo> accessor;	
};
