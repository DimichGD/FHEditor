#pragma once
#include "command_dialog.hpp"

namespace Ui { class WaitDialog; }

class CommandWaitDialog: public CommandDialog
{
	Q_OBJECT

public:
	explicit CommandWaitDialog(bool editing, QModelIndex index, QWidget *parent = nullptr);
	~CommandWaitDialog();

	std::list<Command> resultCommands() override;

private:
	Ui::WaitDialog *ui = nullptr;
};

