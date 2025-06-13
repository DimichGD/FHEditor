#pragma once
#include "simple_chooser_dialog.hpp"
#include <QPushButton>

class SelectorButton: public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(int id MEMBER id NOTIFY idChanged)

public:
	SelectorButton(QWidget *parent = nullptr);
	void setSource(SimpleChooserDialog::Source source) { this->source = source; }

signals:
	void idChanged(int id);

protected slots:
	void changeId(int id);
	void buttonClicked(bool);

private:
	SimpleChooserDialog::Source source;
	int id = 0;
};

