#pragma once
#include "event.hpp"
#include <QDialog>

class CommandDialog: public QDialog
{
	Q_OBJECT

public:
	CommandDialog(QWidget *parent = nullptr): QDialog(parent) {}

	virtual std::list<Command> resultCommands() = 0;

protected:
	int indent = 0;
};

