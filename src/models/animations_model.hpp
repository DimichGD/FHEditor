#pragma once
#include "base_model.hpp"

class AnimationsModel: public BaseModel
{
	Q_OBJECT

public:
	explicit AnimationsModel(QObject *parent = nullptr)
		: BaseModel(&accessor, 2, parent) {}

protected:
	QVariant displayRoleData(int row, int column, Triple pointer) const override;
	QVariant editRoleData(int row, int column, Triple pointer) const override;
	QVariant userRoleData(int row, int column, Triple pointer) const override;
	void setEditRoleData(int row, int column, const QVariant &value, Triple pointer) override;

private:
	Accessor<Animation> accessor;
};

