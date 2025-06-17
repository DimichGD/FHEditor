#pragma once
#include "command_dialog.hpp"
#include "event.hpp"
#include <QDialog>
#include <QModelIndex>

namespace Ui { class CreateCommandDialog; }

class CreateCommandDialog: public QDialog
{
	Q_OBJECT

public:
	explicit CreateCommandDialog(QModelIndex index, QWidget *parent = nullptr);
	~CreateCommandDialog();

	std::list<Command> resultCommands();

protected:
	void openShowTextDialog();
	void openPlaySEDialog();

private:
	Ui::CreateCommandDialog *ui = nullptr;
	CommandDialog *dialog = nullptr;
	QModelIndex currentIndex;
};

