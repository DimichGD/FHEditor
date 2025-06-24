#pragma once
#include "database.hpp"
#include <QAbstractTableModel>

class BaseModel: public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit BaseModel(IAccessor *accessor, int columns, QObject *parent = nullptr);

	QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
	QModelIndex parent(const QModelIndex &child = {}) const override;
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	//bool hasElement(int row);
	void clearElement(int row);
	bool insertRows(int row, int count, const QModelIndex &parent = {}) override;
	bool removeRows(int row, int count, const QModelIndex &parent = {}) override;

protected:
	virtual QVariant dataForDisplay(int row, int column) const = 0;
	virtual QVariant iconForDisplay(int row, int column) const;
	virtual QVariant dataForMapper(int row, int column) const;
	virtual void setDataFromMapper(int row, int column, const QVariant &value);

private:
	int columns = 1;
	QStringList headerTitle;
	IAccessor *accessor = nullptr;
};

