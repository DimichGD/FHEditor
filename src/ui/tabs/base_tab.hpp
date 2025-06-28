#pragma once
#include <QWidget>

class BaseTab: public QWidget
{
	Q_OBJECT

public:
	BaseTab(QWidget *parent): QWidget(parent) {}
};
