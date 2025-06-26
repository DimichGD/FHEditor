#pragma once
#include "effect.hpp"
#include <QAbstractTableModel>
#include <QAbstractItemModel>

class ItemEffectsModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum
	{
		CODE = Qt::UserRole + 0,
		DATA = Qt::UserRole + 1,
	};

	explicit ItemEffectsModel(QObject *parent = nullptr);
	void setEffects(std::vector<Effect> *effects);

	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void addEffect();
	void setEffect(int row, Effect &&effect);
	void removeEffect(int row);

private:
	std::vector<Effect> *effects = nullptr;
};

