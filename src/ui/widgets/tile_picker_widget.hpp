#pragma once
#include <QWidget>

namespace Ui { class TilePickerWidget; }

class TilePickerWidget: public QWidget
{
	Q_OBJECT

public:
	TilePickerWidget(QWidget *parent = nullptr);
	~TilePickerWidget();

	void setTileSet(int id);
	void setCurrentIndex(int index);

private:
	Ui::TilePickerWidget *ui = nullptr;
	std::array<QPixmap, 6> pixmaps;
};

