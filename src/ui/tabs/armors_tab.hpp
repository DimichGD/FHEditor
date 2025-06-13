#pragma once

#include <QWidget>

namespace Ui {
class ArmorsTab;
}

class ArmorsTab: public QWidget
{
	Q_OBJECT

public:
	explicit ArmorsTab(QWidget *parent = nullptr);
	~ArmorsTab();

private:
	Ui::ArmorsTab *ui;
};

