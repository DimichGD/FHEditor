#include "attrib_combo_box.hpp"

AttribComboBox::AttribComboBox(QWidget *parent): QComboBox(parent)
{
	static QStringList attribList = {
		"Max HP", "Max MP", "Attack", "Defense", "M. Attack", "M. Defense", "Agility", "Luck",
	};

	this->addItems(attribList);
}
