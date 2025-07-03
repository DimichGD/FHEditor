#pragma once
//#include "effect.hpp"
#include "items_model.hpp"
//#include "base_model.hpp"
#include <QAbstractProxyModel>
#include <QAbstractTableModel>
//#include <QAbstractItemModel>

class ItemEffectsModel: public QAbstractTableModel
{
public:
	ItemEffectsModel(ItemsModel *sourceModel, QObject *parent);
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	void setItemIndex(int index);

	Effect *effect(int index);
	int effectCode(int index);
	int effectData(int index);

	void addEffect();
	void setEffect(int index, const Effect &effect);
	void removeEffect(int index);

private:
	ItemsModel *itemsModel = nullptr;
	std::vector<Effect> *effects = nullptr;
	int itemIndex = -1;
};

/*class ItemEffectsModel: public QAbstractProxyModel
{
public:
	ItemEffectsModel(QAbstractItemModel *sourceModel, QObject *parent);

	QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override;
	QModelIndex parent(const QModelIndex &child = {}) const override;
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;
	QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
	QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;

	void setItemIndex(int index);

protected:
	void sourceModelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles);

private:
	int itemIndex = -1;
};*/
