#pragma once
#include <QItemSelectionModel>

class EventContentSelectionModel: public QItemSelectionModel
{
	Q_OBJECT

public:
	explicit EventContentSelectionModel(QAbstractItemModel *model, QObject *parent = nullptr):
		QItemSelectionModel(model, parent) {}

public slots:
	//void select(const QModelIndex &index, SelectionFlags command) override;
	void select(const QItemSelection &selection, SelectionFlags flags) override;
};

