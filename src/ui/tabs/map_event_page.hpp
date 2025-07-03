#pragma once
#include "map_event.hpp"
#include "data_mapper.hpp"
#include "map_event_pages_model.hpp"

#include <QWidget>
#include <QCheckBox>

namespace Ui { class MapEventPage; }

class MapEventPage: public QWidget
{
	Q_OBJECT

public:
	MapEventPage(QWidget *parent);
	MapEventPage(MapEventPagesModel *model, int index, QWidget *parent);
	~MapEventPage();

	void connectCheckBoxToWidget(QCheckBox *checkBox, QWidget *widget);
	//void connectCheckBoxToWidget(QCheckBox *checkBox, QList<QWidget *> widgets);

private:
	DataMapper *mapper = nullptr;
	Ui::MapEventPage *ui = nullptr;
	MapEventPagesModel *model = nullptr;
	//Page *page = nullptr;
};

