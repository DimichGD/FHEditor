#pragma once
#include <QWidget>

namespace Ui {
class TypesTab;
}

class QTableWidget;

class TypesTab: public QWidget
{
	Q_OBJECT

public:
	explicit TypesTab(QWidget *parent = nullptr);
	~TypesTab();

	void init();
	void fillTable(QTableWidget *widget, std::vector<std::string> &strings);

private:
	Ui::TypesTab *ui;
};

