#pragma once
#include "base_model.hpp"
#include "animation.hpp"

class AnimationsModel: public BaseModel2
{
public:
	AnimationsModel(QObject *parent = nullptr);
	Animation *animation(int row);

protected:
	QVariant data(int id, int column) const override;
	void setData(int id, int column, const QVariant &value) override;

private:
	Accessor<Animation> accessor;
};

