#include "item_effects_model.hpp"

ItemEffectsModel::ItemEffectsModel(QObject *parent)
	: QAbstractTableModel(parent) {}

void ItemEffectsModel::setEffects(std::vector<Effect> *effects)
{
	beginResetModel();
	this->effects = effects;
	endResetModel();
}

int ItemEffectsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return effects ? effects->size() : 0;
}

int ItemEffectsModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return 2;
}

QVariant ItemEffectsModel::data(const QModelIndex &index, int role) const
{
	if (!effects || !index.isValid())
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
	beginResetModel(); // FIXME: replace with insert
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
	beginResetModel(); // FIXME: replace with remove
	effects->erase(effects->begin() + row);
	endResetModel();
}
