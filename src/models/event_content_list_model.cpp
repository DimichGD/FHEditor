#include "event_content_list_model.hpp"
#include "event.hpp"


void EventContentListModel::load(std::list<Command> *list)
{
	//currentEvent = event;
	commandList = list;
	emit dataChanged(index(0), index(rowCount()));
}

int EventContentListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return commandList ? commandList->size() : 0;
}

QVariant EventContentListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == Qt::UserRole + 1)
	{
		Command::It it = commandList->begin();
		std::advance(it, index.row());
		return QVariant::fromValue(it);
	}

	return QVariant();
}

void EventContentListModel::removeCommands(int row, int count)
{
	QAbstractListModel::beginRemoveRows(QModelIndex(), row, row + count);

	std::list<Command>::iterator begin = commandList->begin();
	std::advance(begin, row);

	std::list<Command>::iterator end = begin;
	std::advance(end, count);

	commandList->erase(begin, end);

	QAbstractListModel::endRemoveRows();
}

void EventContentListModel::insertCommands(int row, std::list<Command> &&otherList)
{
	QAbstractListModel::beginInsertRows(QModelIndex(), row, row + otherList.size() - 1);

	std::list<Command>::iterator begin = commandList->begin();
	std::advance(begin, row);

	commandList->splice(begin, otherList);

	QAbstractListModel::endInsertRows();
}
