#pragma once
#include "tilemap.hpp"
#include <QWidget>

namespace Ui { class MapTab; }

struct Map;
class MapInfoModel;
class TilePickerView;
class QCheckBox;
class QButtonGroup;
class QProcess;

class MapTab: public QWidget
{
	Q_OBJECT

public:
	explicit MapTab(QWidget *parent = nullptr);
	~MapTab();

	void init();
	void loadMap(int id);

public slots:
	void mapInfoTableClicked(const QModelIndex &);

signals:
	void mapLoadTime(int msecs);
	void mapLoaded(Map *map);

private:
	Ui::MapTab *ui = nullptr;
	int currentMapId = 0;
	Map *currentMap = nullptr;
	MapInfoModel *model = nullptr;
	TileMap tileMap;
	std::array<TilePickerView *, 6> tilePickerViews;
	std::array<QCheckBox *, 6> layerCheckBoxes;
	//QButtonGroup *layersCheckBoxGroup = nullptr;
	QProcess *process = nullptr;
};

