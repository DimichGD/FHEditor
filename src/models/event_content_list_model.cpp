#include "event_content_list_model.hpp"
#include "event.hpp"


EventContentListModel::EventContentListModel(QObject *parent)
	: QAbstractListModel(parent) {}

void EventContentListModel::load(std::list<Command> *list)
{
	beginResetModel();
	commandList = list;
	endResetModel();
}


int EventContentListModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return commandList ? commandList->size() : 0;
}

QVariant EventContentListModel::data(const QModelIndex &index, int role) const
{
	if (!commandList)
		return QVariant();

	if (!index.isValid())
		return QVariant();

	if (role == Qt::UserRole + 1)
	{
		Command::Iterator it = std::next(commandList->begin(), index.row());
		return QVariant::fromValue(it);
	}

	return QVariant();
}


void EventContentListModel::removeCommands(int row, int count)
{
	if (!commandList)
		return;

	QAbstractListModel::beginRemoveRows(QModelIndex(), row, row + count);

	std::list<Command>::iterator begin = std::next(commandList->begin(), row);
	std::list<Command>::iterator end = std::next(begin, count);
	commandList->erase(begin, end);

	QAbstractListModel::endRemoveRows();
}

void EventContentListModel::insertCommands(int row, std::list<Command> otherList)
{
	if (!commandList)
		return;

	QAbstractListModel::beginInsertRows(QModelIndex(), row, row + otherList.size() - 1);

	std::list<Command>::iterator begin = std::next(commandList->begin(), row);
	commandList->splice(begin, otherList);

	QAbstractListModel::endInsertRows();
}
