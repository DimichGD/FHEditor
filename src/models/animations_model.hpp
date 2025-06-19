#pragma once
#include "base_model.hpp"

class AnimationsModel : public BaseModel
{
	Q_OBJECT

public:
	explicit AnimationsModel(QObject *parent = nullptr)
		: BaseModel(&accessor, 2, parent) {}

protected:
	QVariant dataForDisplay(int row, int column) const override;

private:
	Accessor<Animation> accessor;
};

