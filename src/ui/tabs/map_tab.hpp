#pragma once
#include "base_tab.hpp"
#include "map_event_tool.hpp"
#include "tile_paint_tool.hpp"
#include "tile_picker_tool.hpp"
#include "tile_map.hpp"
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
	MapTab(QWidget *parent = nullptr);
	~MapTab();

	void init();

private:
	void loadMap(int id);

public slots:
	void mapInfoTableClicked(int row);

signals:
	void mapLoaded(TileMap *tileMap);
	void selectMapEvent(int eventId);

private:
	Ui::MapTab *ui = nullptr;
	MapInfoModel *model = nullptr;
	TileMap tileMap;
	std::array<QCheckBox *, 6> layerCheckBoxes;
	QProcess *process = nullptr;

	TilePaintTool *tilePaintTool = nullptr;
	MapEventTool *mapEventTool = nullptr;
	TilePickerTool *tilePickerTool = nullptr;
	std::array<MapViewTool *, 3> mapViewTools;

	QIcon expandIcon;
	QIcon collapseIcon;
};

