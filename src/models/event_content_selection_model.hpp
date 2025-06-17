#pragma once
#include <QItemSelectionModel>

class EventContentSelectionModel: public QItemSelectionModel
{
	Q_OBJECT

public:
	explicit EventContentSelectionModel(QAbstractItemModel *model, QObject *parent = nullptr):
		QItemSelectionModel(model, parent) {}

public slots:
	void select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags flags) override;
};

