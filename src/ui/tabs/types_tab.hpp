#pragma once
#include <QWidget>

namespace Ui { class TypesTab; }

class QTableWidget;

class TypesTab: public QWidget
{
	Q_OBJECT

public:
	explicit TypesTab(QWidget *parent = nullptr);
	~TypesTab();

	void init();
	void fillTable(QTableWidget *widget, const std::vector<QString> &strings);

private:
	Ui::TypesTab *ui = nullptr;
};

