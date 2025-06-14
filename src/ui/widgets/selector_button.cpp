#include "selector_button.hpp"
#include "database.hpp"

#include <QEvent>
#include <QStandardItem>

SelectorButton::SelectorButton(QWidget *parent): QPushButton(parent)
{
	connect(this, &QPushButton::clicked, this, &SelectorButton::buttonClicked);
	connect(this, &SelectorButton::idChanged, this, &SelectorButton::changeId);
}

void SelectorButton::changeId(int id)
{
	try {
	// TODO: do not get data from database, it need to be from uncommited copies
	if (source == SimpleChooserDialog::ANIMATION)
	{
		Animation *value = Database::Get()->value<Animation>(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::STATE)
	{
		State *value = Database::Get()->value<State>(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::SKILL)
	{
		Skill *value = Database::Get()->value<Skill>(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::SWITCH)
	{
		QString value = Database::Get()->system()->switches.at(id);
		setText(value); // TODO: '?' if id >= switches.size()
	}
	else if (source == SimpleChooserDialog::VARIABLE)
	{
		QString value = Database::Get()->system()->variables.at(id);
		setText(value); // TODO: '?' if id >= variables.size()
	}
	else if (source == SimpleChooserDialog::ITEM)
	{
		Item *value = Database::Get()->value<Item>(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::COMMON_EVENT)
	{
		Event *value = Database::Get()->value<Event>(id);
		setText(value ? value->name : "?");
	}
	} catch (std::exception &e) // TODO: remove this?
	{ qDebug() << "idChanged(" << id << ") exception with source" << source; }
}

void SelectorButton::buttonClicked(bool)
{
	static QStringList titleMap = {
		"Animations",
		"States",
		"Skills",
		"Switches",
		"Variables",
		"Items",
		"Common Events"
	};

	SimpleChooserDialog dialog(SimpleChooserDialog::Source(source), id, this);
	dialog.setWindowTitle(titleMap[source]);

	if (dialog.exec())
	{
		setProperty("id", dialog.result());
		changeId(dialog.result());
	}
}
