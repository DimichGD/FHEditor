#include "item_effects_model.hpp"

ItemEffectsModel::ItemEffectsModel(std::vector<Effect> *effects, QObject *parent)
	: QAbstractTableModel(parent)
{
	this->effects = effects;
}

int ItemEffectsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return effects->size();
}

int ItemEffectsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return 2;
}

QVariant ItemEffectsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == CODE)
		return effects->at(index.row()).code;

	if (role == DATA)
		return effects->at(index.row()).dataId;

	if (role != Qt::DisplayRole)
		return QVariant();

	QStringList list = effectToStringList(&effects->at(index.row()));
	switch (index.column())
	{
		case 0: return list[0];
		case 1: return list[1];
	}

	return QVariant();
}

QVariant ItemEffectsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();

	switch (section)
	{
		case 0: return "Type";
		case 1: return "Content";
	}

	return QVariant();
}

void ItemEffectsModel::addEffect()
{
	beginResetModel();
	effects->emplace_back();
	endResetModel();
}

void ItemEffectsModel::setEffect(int row, Effect &&effect)
{
	beginResetModel();
	effects->at(row) = effect;
	endResetModel();
}

void ItemEffectsModel::removeEffect(int row)
{
	beginResetModel();
	effects->erase(effects->begin() + row);
	endResetModel();
}
