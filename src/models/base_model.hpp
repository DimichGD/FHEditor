#pragma once
#include "database.hpp"
#include <QAbstractTableModel>
#include <QAbstractItemModel>

struct Triple // TODO: rename this and pointer argument
{
	uint64_t row: 32;
	uint64_t column: 32;
};

template<typename T>
void *pack(T &value)
{
	uint64_t result = *reinterpret_cast<uint64_t *>(&value);
	return reinterpret_cast<void *>(result);
}

template<typename T>
T unpack(void *value)
{
	uint64_t result = reinterpret_cast<uint64_t>(value);
	return *reinterpret_cast<T *>(&result);
}



class BaseModel: public QAbstractItemModel
{
public:
	BaseModel(IAccessor *accessor, int columns, QObject *parent);

	void reset();
	QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
	QModelIndex parent(const QModelIndex &child = {}) const override;
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	void clearElement(int row);
	bool insertRows(int row, int count, const QModelIndex &parent = {}) override;
	bool removeRows(int row, int count, const QModelIndex &parent = {}) override;

protected:
	void updateDisplayRole(const QModelIndex &index);
	virtual QVariant displayRoleData(int row, int column, Triple pointer) const = 0;
	virtual QVariant editRoleData(int row, int column, Triple pointer) const = 0;
	virtual QVariant userRoleData(int row, int column, Triple pointer) const;
	virtual void setEditRoleData(int row, int column, const QVariant &value, Triple pointer) = 0;

private:
	int columns = 0;
	QStringList headerTitle;
	IAccessor *accessor = nullptr;
};
