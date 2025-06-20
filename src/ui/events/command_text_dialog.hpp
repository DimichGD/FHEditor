#pragma once
#include "command_dialog.hpp"
#include "event.hpp"
#include <QList>
#include <QModelIndex>
#include <QDialog>

namespace Ui { class CommandTextDialog; }

class CommandTextDialog: public CommandDialog
{
	Q_OBJECT

public:
	explicit CommandTextDialog(bool editing, QList<QModelIndex> indices, QWidget *parent = nullptr);
	~CommandTextDialog();
	//void makeChanges();
	std::list<Command> resultCommands() override;

protected slots:
	void openIconPickerDialog(QString faceName, int faceIndex);

private:
	//Command::It parentIt;
	//bool editing = false;
	//int selectionSize = 0;
	//Event *event = nullptr;
	//Command::It rootCommand;
	QString faceName {};
	int faceIndex = 0;
	int indent = 0;
	Ui::CommandTextDialog *ui = nullptr;
};

