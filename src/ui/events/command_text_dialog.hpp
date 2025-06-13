#pragma once
#include "event.hpp"
#include <QList>
#include <QModelIndex>
#include <QDialog>

namespace Ui { class CommandTextDialog; }

class CommandTextDialog: public QDialog
{
	Q_OBJECT

public:
	explicit CommandTextDialog(bool editing, QList<QModelIndex> indices, QWidget *parent = nullptr);
	~CommandTextDialog();
	void makeChanges();

private:
	//Command::It parentIt;
	bool editing = false;
	int selectionSize = 0;
	Event *event = nullptr;
	Command::It rootCommand;
	Ui::CommandTextDialog *ui = nullptr;
};

