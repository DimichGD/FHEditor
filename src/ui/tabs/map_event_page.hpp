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
	explicit MapEventPage(MapEventPagesModel *model, int index, Page *page, QWidget *parent = nullptr);
	~MapEventPage();

	void connectCheckBoxToWidget(QCheckBox *checkBox, QWidget *widget);
	//void connectCheckBoxToWidget(QCheckBox *checkBox, QList<QWidget *> widgets);

private:
	DataMapper *mapper = nullptr;
	Ui::MapEventPage *ui = nullptr;
};

