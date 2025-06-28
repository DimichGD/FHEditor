#pragma once
#include "base_tab.hpp"
#include "map_event_tool.hpp"
#include "tile_paint_tool.hpp"
#include "tile_picker_tool.hpp"
#include "tilemap.hpp"
#include "map_view.hpp"
#include <QWidget>
#include <memory>

namespace Ui { class MapTab; }

struct Map;
class MapInfoModel;
class TilePickerView;
class QCheckBox;
class QButtonGroup;
class QProcess;


class MapTab: public BaseTab
{
	Q_OBJECT

public:
	explicit MapTab(QWidget *parent = nullptr);
	~MapTab();

	void init();
	void loadMap(int id);
	int mapId() { return currentMapId; } // FIXME: need id for saving in main_window.cpp

public slots:
	void mapInfoTableClicked(int row);

signals:
	//void mapLoadTime(int msecs);
	//void mapLoaded(Map *map);
	void mapLoaded(TileMap *tileMap);
	void selectMapEvent(int eventId);
	//void addMapEvent(MapEvent event);
	//void addMapEvent(int eventId);

private:
	Ui::MapTab *ui = nullptr;
	int currentMapId = 0;
	//Map *currentMap = nullptr;
	MapInfoModel *model = nullptr;
	TileMap tileMap;
	//std::array<TilePickerView *, 6> tilePickerViews;
	std::array<QCheckBox *, 6> layerCheckBoxes;
	//QButtonGroup *layersCheckBoxGroup = nullptr;
	QProcess *process = nullptr;

	TilePaintTool *tilePaintTool = nullptr;
	MapEventTool *mapEventTool = nullptr;
	TilePickerTool *tilePickerTool = nullptr;
	std::array<MapViewTool *, 3> mapViewTools;
};

