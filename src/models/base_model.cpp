#include "base_model.hpp"

BaseModel::BaseModel(IAccessor *accessor, int columns, QObject *parent): QAbstractItemModel(parent)
{
	this->accessor = accessor;
	this->columns = columns;

	if (columns == 3)
		headerTitle = { "ID", "Icon", "Name" };
	else
		headerTitle = { "ID", "Name" };
}

void BaseModel::reset()
{
	beginResetModel();
	endResetModel();
}

QModelIndex BaseModel::index(int row, int column, const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return createIndex(row, column);
}

QModelIndex BaseModel::parent(const QModelIndex &child) const
{
	Q_UNUSED(child)
	return QModelIndex();
}

int BaseModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return accessor ? accessor->size() : 0;
}

int BaseModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return columns;
}

QVariant BaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();

	return headerTitle[section];
}

QVariant BaseModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= rowCount())
	{
		qDebug() << "ItemsModel::data index.row() >= rowCount()";
		return QVariant();
	}

	if (!accessor->hasElement(index.row()))
		return QVariant();

	Triple value = unpack<Triple>(index.internalPointer());
	switch (role)
	{
		case Qt::DisplayRole: return displayRoleData(index.row(), index.column(), value);
		case Qt::EditRole: return editRoleData(index.row(), index.column(), value);
		case Qt::UserRole: return userRoleData(index.row(), index.column(), value);
	}

	return QVariant();
}

bool BaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	if (role != Qt::EditRole)
		return false;

	if (!accessor->hasElement(index.row()))
		return false;

	Triple triple = unpack<Triple>(index.internalPointer());
	setEditRoleData(index.row(), index.column(), value, triple);

	return true;
}

void BaseModel::clearElement(int row)
{
	accessor->clearElement(row);

	emit dataChanged(index(row, 1), index(row, 2), { Qt::DisplayRole });
	emit dataChanged(index(row, 1), index(row, Item::COUNT - 1), { Qt::EditRole });
}

bool BaseModel::insertRows(int row, int count, const QModelIndex &parent)
{
	// TODO: sanity check
	beginInsertRows(parent, row, row + count - 1);
	accessor->insertToEnd(count);
	endInsertRows();
	return true;
}

bool BaseModel::removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row + 1, row + count);
	accessor->removeFromEnd(count);
	endRemoveRows();
	return true;
}

void BaseModel::updateDisplayRole(const QModelIndex &index)
{
	emit dataChanged(index, index, { Qt::DisplayRole });
}

QVariant BaseModel::userRoleData(int row, int column, Triple pointer) const
{
	Q_UNUSED(row)
	Q_UNUSED(column)
	Q_UNUSED(pointer)
	return QVariant();
}

