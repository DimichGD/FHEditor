#include "base_model.hpp"

BaseModel2::BaseModel2(IAccessor *accessor, QObject *parent): QAbstractTableModel(parent)
{
	this->accessor = accessor;
}

int BaseModel2::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return accessor->size() - 1;
}

int BaseModel2::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return accessor->columns();
}

QVariant BaseModel2::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	if (!accessor->hasElement(index.row() + 1))
		return QVariant();

	return data(index.row() + 1, index.column());
}

bool BaseModel2::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return false;

	if (!accessor->hasElement(index.row() + 1))
		return false;

	setData(index.row() + 1, index.column(), value);
	emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

	return true;
}

void BaseModel2::changeCount(int count)
{
	if (count < accessor->size())
	{
		beginRemoveRows(QModelIndex(), count, accessor->size() - 1);
		accessor->removeFromEnd(accessor->size() - count);
		endRemoveRows();
	}
	else if (count > accessor->size())
	{
		beginInsertRows(QModelIndex(), accessor->size(), count - 1);
		accessor->insertToEnd(count - accessor->size());
		endInsertRows();
	}
}

void BaseModel2::clearRow(int row)
{
	accessor->clearElement(row);
	emit dataChanged(index(row, 0), index(row, accessor->columns() - 1), { Qt::DisplayRole, Qt::EditRole });
}

void BaseModel2::reset()
{
	beginResetModel();
	endResetModel();
}



