#pragma once
#include <QWidget>

namespace Ui { class IconWidget; }

class IconWidget: public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int iconIndex MEMBER index READ iconIndex WRITE setIconIndex NOTIFY iconChanged)

public:
	explicit IconWidget(QWidget *parent = nullptr);
	~IconWidget();

	int iconIndex() const { return index; }
	void setIconIndex(int iconIndex);

public slots:
	void openPickerDialog();

signals:
	void iconChanged(int iconIndex);

private:
	Ui::IconWidget *ui = nullptr;
	int index = 0;
};

