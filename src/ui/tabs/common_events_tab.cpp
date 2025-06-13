#include "common_events_tab.hpp"
#include "database.hpp"
#include "data_mapper.hpp"
#include "command_factory.hpp"
#include "common_events_model.hpp"
#include "ui_common_events_tab.h"

#include <QDataWidgetMapper>
#include <QStyledItemDelegate>
#include <QMenu>

Q_DECLARE_METATYPE(QSharedPointer<ICommand>);
Q_DECLARE_METATYPE(Command::It);


CommonEventsTab::CommonEventsTab(QWidget *parent):
	QWidget(parent), ui(new Ui::CommonEventsTab)
{
	ui->setupUi(this);
	ui->eventSwitchButton->setSource(SimpleChooserDialog::SWITCH);

	/*contextMenu = new QMenu(this);
	contextMenu->addAction(ui->actionCommandNew);
	contextMenu->addAction(ui->actionCommandEdit);
	contextMenu->addSeparator();
	contextMenu->addAction(ui->actionCommandCollapseAll);
	contextMenu->addAction(ui->actionCommandExpandAll);
	contextMenu->addSeparator();
	contextMenu->addAction(ui->actionCommandDelete);

	connect(ui->actionCommandNew, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandNewTriggered);
	connect(ui->actionCommandEdit, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandEditTriggered);
	connect(ui->actionCommandDelete, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandDeleteTriggered);
	connect(ui->eventContentList, &EventContentList::customContextMenuRequested, this, &CommonEventsTab::contextMenuRequested);*/

	connect(ui->eventsTable, &BaseTable::rowSelected, this, &CommonEventsTab::eventRowSelected);
	connect(ui->eventsNameFilter, &QLineEdit::textChanged, ui->eventsTable, &BaseTable::setFilterText);

	connect(ui->eventTriggerComboBox, &QComboBox::currentIndexChanged, [this](int index)
		{ ui->eventSwitchButton->setEnabled(index != 0); });
}

CommonEventsTab::~CommonEventsTab()
{
	delete ui;
}

void CommonEventsTab::init()
{
	// TODO: delete and nullify model pointer
	// delete via deleteLater() ?
	model = new CommonEventsModel(ui->eventsTable);
	ui->eventsTable->setModel2(model);
	ui->eventsTable->hideColumn(1);

	mapper = new DataMapper(this);
	mapper->setModel(model);
	mapper->addWidgets({
		{ ui->eventNameEdit, Event::NAME },
		{ ui->eventTriggerComboBox, Event::TRIGGER },
		{ ui->eventSwitchButton, Event::SWITCH_ID },
	});
	ui->eventsTable->selectRow(0);
}

void CommonEventsTab::eventRowSelected(int row)
{
	currentEvent = model->eventFromRow(row);
	if (!currentEvent)
	{
		//ui->eventContentList->clear();
		mapper->toFirst();
		//enableGroupBoxes(false);
		return;
	}

	//if (!ui->generalBox->isEnabled())
	//	enableGroupBoxes(true);

	mapper->setCurrentIndex(row);

	//ui->eventContentList->clear();
	ui->eventContentList->loadList(currentEvent, &currentEvent->list);
}

/*void CommonEventsTab::contextMenuRequested(const QPoint &pos)
{
	QModelIndex index = ui->eventContentList->indexAt(pos);
	if (index.isValid())
	{
		Command::It command = index.data(Qt::UserRole + 1).value<Command::It>();

		ui->actionCommandNew->setEnabled(command->parameters->canAdd());
		ui->actionCommandEdit->setEnabled(command->parameters->canEdit());
		ui->actionCommandDelete->setEnabled(command->parameters->canDelete());
	}
	else
	{
		ui->actionCommandNew->setEnabled(false);
		ui->actionCommandEdit->setEnabled(false);
		ui->actionCommandDelete->setEnabled(false);
	}

	contextMenu->exec(ui->eventContentList->viewport()->mapToGlobal(pos));
}*/

void CommonEventsTab::applyButtonClicked()
{
	//
}

