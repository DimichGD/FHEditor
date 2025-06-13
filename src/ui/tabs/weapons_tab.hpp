#pragma once

#include <QWidget>

namespace Ui {
class WeaponsTab;
}

class WeaponsTab : public QWidget
{
	Q_OBJECT

public:
	explicit WeaponsTab(QWidget *parent = nullptr);
	~WeaponsTab();

private:
	Ui::WeaponsTab *ui;
};

