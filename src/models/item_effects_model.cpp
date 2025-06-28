#include "item_effects_model.hpp"
#include "base_model.hpp"
#include "item.hpp"

ItemEffectsModel::ItemEffectsModel(QAbstractItemModel *sourceModel, QObject *parent)
	: QAbstractProxyModel(parent)
{
	setSourceModel(sourceModel);
	connect(sourceModel, &QAbstractItemModel::dataChanged, this, &ItemEffectsModel::sourceModelChanged);
}

QModelIndex ItemEffectsModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return createIndex(row, column);
}

QModelIndex ItemEffectsModel::parent(const QModelIndex &child) const
{
	Q_UNUSED(child)
	return QModelIndex();
}

int ItemEffectsModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	if (itemIndex < 0)
		return 0;

	return sourceModel()->index(itemIndex, Item::EFFECTS).data(Qt::UserRole).toInt();
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

Qt::ItemFlags ItemEffectsModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
}

QModelIndex ItemEffectsModel::mapToSource(const QModelIndex &proxyIndex) const
{
	if (!proxyIndex.isValid())
		return QModelIndex();

	Triple value;
	value.row = proxyIndex.row();
	value.column = proxyIndex.column();
	return createIndex(itemIndex, Item::EFFECTS, pack(value));
}

QModelIndex ItemEffectsModel::mapFromSource(const QModelIndex &sourceIndex) const
{
	if (!sourceIndex.isValid())
		return QModelIndex();

	Triple value = unpack<Triple>(sourceIndex.internalPointer());
	return createIndex(value.row, value.column);
}

void ItemEffectsModel::setItemIndex(int index)
{
	beginResetModel();
	itemIndex = index;
	endResetModel();
}

void ItemEffectsModel::sourceModelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
	//if (roles.contains(Qt::EditRole))
	{
		if (topLeft.column() <= Item::EFFECTS && bottomRight.column() >= Item::EFFECTS)
		{
			beginResetModel();
			endResetModel();
		}
	}
}
