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
	void openWaitDialog();
	void openPlayBGMDialog();
	void openPlayBGSDialog();
	void openPlayMEDialog();
	void openPlaySEDialog();
	void makeGatherFollowersCommand();
	void makeStopSECommand();
	void makeLoopCommand();
	void makeBreakLoopCommand();
	void makeOpenSaveCommand();
	void makeGameOverCommand();

private:
	Ui::CreateCommandDialog *ui = nullptr;
	CommandDialog *dialog = nullptr;
	int indent = 0;
	QModelIndex currentIndex {};
	std::list<Command> commands {};
};

