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
			Animation *value = Database::Get()->accessor<Animation>().value(id);
			setText(value ? value->name : "?");
		}
	}
	else if (source == SimpleChooserDialog::STATE)
	{
		State *value = Database::Get()->accessor<State>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::SKILL)
	{
		Skill *value = Database::Get()->accessor<Skill>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::SWITCH)
	{
		//QString value = Database::Get()->system()->switches.at(id);
		QString value = Database::Get()->switchName(id);
		value = fontMetrics().elidedText(value, Qt::ElideRight, width() - 8);
		setText(value); // TODO: '?' if id >= switches.size()
	}
	else if (source == SimpleChooserDialog::VARIABLE)
	{
		//QString value = Database::Get()->system()->variables.at(id);
		QString value = Database::Get()->variableName(id);
		value = fontMetrics().elidedText(value, Qt::ElideRight, width() - 8);
		setText(value); // TODO: '?' if id >= variables.size()
	}
	else if (source == SimpleChooserDialog::ITEM)
	{
		Item *value = Database::Get()->accessor<Item>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::COMMON_EVENT)
	{
		Event *value = Database::Get()->accessor<Event>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::ACTOR)
	{
		Actor *value = Database::Get()->accessor<Actor>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::CLASS)
	{
		Class *value = Database::Get()->accessor<Class>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::WEAPON)
	{
		Weapon *value = Database::Get()->accessor<Weapon>().value(id);
		setText(value ? value->name : "?");
	}
	else if (source == SimpleChooserDialog::ARMOR)
	{
		Armor *value = Database::Get()->accessor<Armor>().value(id);
		setText(value ? value->name : "?");
	}
	//} catch (std::exception &e) // TODO: remove this
	//{ qDebug() << "idChanged(" << id << ") exception with source" << source; }
}

void SelectorButton::buttonClicked()
{
	if (source == SimpleChooserDialog::EMPTY)
	{
		qDebug() << "SelectorButton source is not set";
		return;
	}

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
