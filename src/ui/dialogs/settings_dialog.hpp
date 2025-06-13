#pragma once
#include <QTableWidgetItem>
#include <QDialog>

namespace Ui { class SettingsDialog; }

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = nullptr);
	~SettingsDialog();

public slots:
	void addGameClicked();
	void removeGameClicked();
	void saveSettings();

protected:
	void addRow(const QString &name, const QString &path);

private:
	Ui::SettingsDialog *ui;
};

