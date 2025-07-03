#pragma once
//#include "map.hpp"
#include "map_event_page.hpp"
#include "map_event_pages_model.hpp"
#include "map_events_model.hpp"
#include "tile_map.hpp"

#include <QWidget>
#include <QPushButton>
#include <QTabBar>

namespace Ui { class MapEventsTab; }

class MapEventsTab: public QWidget
{
	Q_OBJECT

public:
	MapEventsTab(QWidget *parent = nullptr);
	~MapEventsTab();

	void init(TileMap *tileMap);

public slots:
	void mapEventsTableClicked(int row);
	void selectEvent(int id);
	void addMapEvent(MapEvent event);

protected:
	void connectCheckBoxToWidget(QCheckBox *checkBox, QWidget *widget);
	void enableWidgets(bool enabled);
	void setCurrentPage(int index);

private:
	MapEventsModel *model = nullptr;
	MapEventPagesModel *pagesModel = nullptr;
	QTabBar *pagesTabBar = nullptr;
	//Map *currentMap = nullptr;
	TileMap *currentMap = nullptr;
	//std::vector<MapEventPage *> pageWidgets;
	DataMapper *pagesMapper = nullptr;
	DataMapper *mapper = nullptr;
	Ui::MapEventsTab *ui = nullptr;
};

