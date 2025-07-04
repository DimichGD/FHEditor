#include "common_events_tab.hpp"
#include "database.hpp"
#include "data_mapper.hpp"
#include "command_factory.hpp"
#include "common_events_model.hpp"
#include "ui_common_events_tab.h"

#include <QDataWidgetMapper>
#include <QStyledItemDelegate>
#include <QMenu>

//Q_DECLARE_METATYPE(QSharedPointer<ICommandParams>);
Q_DECLARE_METATYPE(Command::Iterator);


CommonEventsTab::CommonEventsTab(QWidget *parent):
	QWidget(parent), ui(new Ui::CommonEventsTab)
{
	ui->setupUi(this);
	ui->eventSwitchButton->setSource(SimpleChooserDialog::SWITCH);
	//ui->undoView->setStack(ui->eventContentList->undoStack);

	/*contextMenu = new QMenu(this);
	contextMenu->addAction(ui->actionCommandNew);
	contextMenu->addAction(ui->actionCommandEdit);
	contextMenu->addSeparator();
	contextMenu->addAction(ui->actionCommandDelete);

	connect(ui->actionCommandNew, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandNewTriggered);
	connect(ui->actionCommandEdit, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandEditTriggered);
	connect(ui->actionCommandDelete, &QAction::triggered, ui->eventContentList, &EventContentList::actionCommandDeleteTriggered);
	connect(ui->eventContentList, &EventContentList::customContextMenuRequested, this, &CommonEventsTab::contextMenuRequested);*/

	model = new CommonEventsModel(ui->eventsTable);
	ui->eventsTable->setModel2(model, Event::NAME);

	for (int i = 0; i < Event::COUNT; i++)
		ui->eventsTable->setColumnHidden(i, true);

	ui->eventsTable->setColumnHidden(Event::ID, false);
	ui->eventsTable->setColumnHidden(Event::NAME, false);

	connect(ui->eventsTable, &BaseTable::rowSelected, this, &CommonEventsTab::eventRowSelected);
	connect(ui->eventsNameFilter, &QLineEdit::textChanged, ui->eventsTable, &BaseTable::setFilterText);

	connect(ui->eventTriggerComboBox, &QComboBox::currentIndexChanged, this, [this](int index)
		{ ui->eventSwitchButton->setEnabled(index != 0); });

	connect(ui->autorunButton, &QPushButton::clicked, [this]()
	{
		//ui->eventContentList->clear();
		ui->eventsTable->setCustomFilter(Event::TRIGGER, 1);
		ui->eventsTable->selectRow(0);
	});

	connect(ui->parallelButton, &QPushButton::clicked, [this]()
	{
		//ui->eventContentList->clear();
		ui->eventsTable->setCustomFilter(Event::TRIGGER, 2);
		ui->eventsTable->selectRow(0);
	});

	connect(ui->clearFilterButton, &QPushButton::clicked, [this]()
	{
		//ui->eventContentList->clear();
		ui->eventsTable->disableCustomFilter();
		ui->eventsTable->selectRow(0);
	});
}

CommonEventsTab::~CommonEventsTab()
{
	delete ui;
}

void CommonEventsTab::init()
{
	// TODO: delete and nullify model pointer
	// delete via deleteLater() ?


	/*QFontMetrics metrics = ui->eventContentList->fontMetrics();
	for (auto &event: Database::Get()->getStorage<Event>())
		if (event.has_value())
			for (auto &command: event.value().list)
				command.parameters->prepare(metrics);*/

	model->reset();
	ui->eventsTable->resizeColumnToContents(0);

	mapper = new DataMapper(model, this);
	mapper->add(ui->eventNameEdit, Event::NAME);
	mapper->add(ui->eventTriggerComboBox, Event::TRIGGER);
	mapper->add(ui->eventSwitchButton, Event::SWITCH_ID);

	ui->eventsTable->selectRow(0);
	//ui->eventContentList->clear();
}

void CommonEventsTab::eventRowSelected(int row)
{
	Event *currentEvent = model->commonEvent(row);
	if (!currentEvent)
	{
		ui->eventContentList->loadList(nullptr);
		mapper->setCurrentIndex(-1);
		//enableGroupBoxes(false);
		return;
	}

	//if (!ui->generalBox->isEnabled())
	//	enableGroupBoxes(true);

	ui->eventContentList->loadList(&currentEvent->list);
	mapper->setCurrentIndex(row);
}

/*void CommonEventsTab::contextMenuRequested(const QPoint &pos)
{
	QModelIndex index = ui->eventContentList->indexAt(pos);
	if (index.isValid())
	{
		auto parameters = Command::iteratorFromIndex(index)->parameters;

		ui->actionCommandNew->setEnabled(parameters->flags() & ICommandParams::CAN_ADD);
		ui->actionCommandEdit->setEnabled(parameters->flags() & ICommandParams::CAN_EDIT);
		ui->actionCommandDelete->setEnabled(parameters->flags() & ICommandParams::CAN_DELETE);
	}
	else
	{
		ui->actionCommandNew->setEnabled(false);
		ui->actionCommandEdit->setEnabled(false);
		ui->actionCommandDelete->setEnabled(false);
	}

	contextMenu->exec(ui->eventContentList->viewport()->mapToGlobal(pos));
}*/

