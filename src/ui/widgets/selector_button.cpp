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
	//try {
	// TODO: do not get data from database, it need to be from uncommited copies
	if (source == SimpleChooserDialog::ANIMATION)
	{
		if (id == -1)
			setText("Normal Attack");

		else if (id == 0)
			setText("None");

		else
		{
			Animation *value = Accessor<Animation>().value(id);
			setText(value ? value->name : "?");
		}
	}
	else if (source == SimpleChooserDialog::STATE)
	{
		State *value = Accessor<State>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::SKILL)
	{
		Skill *value = Accessor<Skill>().value(id);
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
		Item *value = Accessor<Item>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::COMMON_EVENT)
	{
		Event *value = Accessor<Event>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::ACTOR)
	{
		Actor *value = Accessor<Actor>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::CLASS)
	{
		Class *value = Accessor<Class>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::WEAPON)
	{
		Weapon *value = Accessor<Weapon>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::ARMOR)
	{
		Armor *value = Accessor<Armor>().value(id);
		setText(value ? value->name : "?");
	}
	//} catch (std::exception &e) // TODO: remove this
	//{ qDebug() << "idChanged(" << id << ") exception with source" << source; }
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
		"Common Events",
		"Actors",
		"Classes",
		"Weapons",
		"Armors",
	};

	SimpleChooserDialog dialog(SimpleChooserDialog::Source(source), id, this);
	dialog.setWindowTitle(titleMap[source]);

	if (dialog.exec())
	{
		setProperty("id", dialog.result());
		changeId(dialog.result());
	}
}
