#pragma once
#include "accessor.hpp"
#include <QAbstractTableModel>

class BaseModel2: public QAbstractTableModel
{
public:
	BaseModel2(IAccessor *accessor, QObject *parent);
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	void changeCount(int count);
	void clearRow(int row);
	void reset();

protected:
	virtual QVariant data(int id, int column) const = 0;
	virtual void setData(int id, int column, const QVariant &value) = 0;

private:
	IAccessor *accessor = nullptr;
};

