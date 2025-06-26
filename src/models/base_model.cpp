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
	return accessor->size();
}

int BaseModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return columns;
}

QVariant BaseModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	switch (role)
	{
		case Qt::DisplayRole: return dataForDisplay(index.row(), index.column());
		case Qt::EditRole: return dataForMapper(index.row(), index.column());
		case Qt::DecorationRole: return iconForDisplay(index.row(), index.column());
	};

	return QVariant();
}

bool BaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;


	if (role != Qt::EditRole)
		return false;

	setDataFromMapper(index.row(), index.column(), value);
	emit dataChanged(index, index, { Qt::EditRole });
	emit dataChanged(this->index(index.row(), 0), this->index(index.row(), 2), { Qt::DisplayRole });

	return true;
}

QVariant BaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return QVariant();

	return headerTitle[section];
}

/*bool BaseModel::hasElement(int row)
{
	return accessor->hasElement(row);
}*/


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

QVariant BaseModel::iconForDisplay(int row, int column) const
{
	Q_UNUSED(row)
	Q_UNUSED(column)
	return QVariant();
}

QVariant BaseModel::dataForMapper(int row, int column) const
{
	Q_UNUSED(row)
	Q_UNUSED(column)
	return QVariant();
}

void BaseModel::setDataFromMapper(int row, int column, const QVariant &value)
{
	Q_UNUSED(row)
	Q_UNUSED(column)
	Q_UNUSED(value)
}



