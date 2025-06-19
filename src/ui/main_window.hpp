#pragma once
#include <QMainWindow>

namespace Ui { class MainWindow; }

class MapTab;
class MapEventsTab;
class ItemsTab;
class ArmorsTab;
class WeaponsTab;
class CommonEventsTab;
class TypesTab;
class AnimationsTab;

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void loadGame();

protected:
	//

private slots:
	void openSettingsDialog();

private:
	Ui::MainWindow *ui = nullptr;
	MapTab *mapTab = nullptr;
	MapEventsTab *mapEventsTab = nullptr;
	ItemsTab *itemsTab = nullptr;
	ArmorsTab *armorsTab = nullptr;
	WeaponsTab *weaponsTab = nullptr;
	CommonEventsTab *commonEventsTab = nullptr;
	TypesTab *typesTab = nullptr;
	AnimationsTab *animationTab = nullptr;

	int mapTabIndex = 0;
	int mapEventsTabIndex = 0;
	int itemsTabIndex = 0;
	int weaponsTabIndex = 0;
	int armorsTabIndex = 0;
	int commonEventsTabIndex = 0;
	int typesTabIndex = 0;
	int animationTabIndex = 0;
};
