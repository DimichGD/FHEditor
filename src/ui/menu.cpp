#include "menu.hpp"

QMenu *createMenu(QWidget *parent, std::initializer_list<QAction *> actions)
{
	QMenu *menu = new QMenu(parent);

	for (QAction *action: actions)
	{
		if (action)
			menu->addAction(action);
		else
			menu->addSeparator();
	}

	return menu;
}
