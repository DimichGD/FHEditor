#pragma once
#include "command_dialog.hpp"
#include "json_value.hpp"

namespace Ui {class ConditionalBranchDialog; }

class ConditionalBranchDialog : public CommandDialog
{
	Q_OBJECT

public:
	explicit ConditionalBranchDialog(bool editing, QList<QModelIndex> indices, QWidget *parent = nullptr);
	~ConditionalBranchDialog();

	std::list<Command> resultCommands() override;

protected slots:
	void setWidgetsVisible(QString prefix, bool toggled);
	void radioButtonToggled(int index, bool toggled);
	//void fillWidgets(JsonValue &value);

private:
	Ui::ConditionalBranchDialog *ui = nullptr;
	/*Command::Iterator rootCommand; //
	Command::Iterator elseCommand; // move to ctor
	Command::Iterator endCommand; // move to ctor*/
	std::list<Command> bodyList;
	std::list<Command> elseList;
	//bool hadElseBranch = false;
};

