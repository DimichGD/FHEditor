#include "item_effects_model.hpp"

ItemEffectsModel::ItemEffectsModel(ItemsModel *sourceModel, QObject *parent)
	: QAbstractTableModel(parent)
{
	itemsModel = sourceModel;
}

int ItemEffectsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	if (itemIndex < 0 || !effects)
		return 0;

	return effects->size();
}

int ItemEffectsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return 2;
}

QVariant ItemEffectsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();

	return section == 0 ? "Type" : "Content";
}

QVariant ItemEffectsModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	const Effect *effect = &effects->at(index.row());
	switch (index.column())
	{
		case 0: return effectType(effect);
		case 1: return effectValue(effect);
		default: return QVariant();
	}

	return QVariant();
}

void ItemEffectsModel::setItemIndex(int index)
{
	beginResetModel();
	itemIndex = index;
	effects = itemsModel->effects(index);
	endResetModel();
}

Effect *ItemEffectsModel::effect(int index)
{
	return &effects->at(index);
}

int ItemEffectsModel::effectCode(int index)
{
	return effects->at(index).code;
}

int ItemEffectsModel::effectData(int index)
{
	return effects->at(index).dataId;
}

void ItemEffectsModel::addEffect()
{
	beginResetModel();
	effects->emplace_back();
	endResetModel();
}

void ItemEffectsModel::setEffect(int index, const Effect &effect)
{
	beginResetModel();
	effects->at(index) = effect;
	endResetModel();
}

void ItemEffectsModel::removeEffect(int index)
{
	beginResetModel();
	effects->erase(effects->begin() + index);
	endResetModel();
}

