#pragma once
#include "map.hpp"
#include "map_event_pages_model.hpp"
#include "map_events_model.hpp"

#include <QWidget>

namespace Ui { class MapEventsTab; }

class MapEventsTab: public QWidget
{
	Q_OBJECT

public:
	explicit MapEventsTab(QWidget *parent = nullptr);
	~MapEventsTab();

	void init(Map *map);

public slots:
	void mapEventsTableClicked(int row);
	void selectEvent(int id);

private:
	MapEventsModel *model = nullptr;
	MapEventPagesModel *pagesModel = nullptr;
	Map *currentMap = nullptr;
	Ui::MapEventsTab *ui = nullptr;
};

