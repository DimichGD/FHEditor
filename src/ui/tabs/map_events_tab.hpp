#pragma once
//#include "map.hpp"
#include "map_event_pages_model.hpp"
#include "map_events_model.hpp"
#include "tilemap.hpp"

#include <QWidget>
#include <QPushButton>

namespace Ui { class MapEventsTab; }

class MapEventsTab: public QWidget
{
	Q_OBJECT

public:
	explicit MapEventsTab(QWidget *parent = nullptr);
	~MapEventsTab();

	void init(TileMap *tileMap);

public slots:
	void mapEventsTableClicked(int row);
	void selectEvent(int id);
	void addMapEvent(MapEvent event);

private:
	MapEventsModel *model = nullptr;
	MapEventPagesModel *pagesModel = nullptr;
	//Map *currentMap = nullptr;
	TileMap *currentMap = nullptr;
	Ui::MapEventsTab *ui = nullptr;
};

