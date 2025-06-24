#pragma once
#include <QMenu>
#include <initializer_list>

QMenu *createMenu(QWidget *parent, std::initializer_list<QAction *> actions);
