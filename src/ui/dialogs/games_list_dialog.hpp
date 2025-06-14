#pragma once
#include <QDialog>

namespace Ui { class SettingsDialog; }

class GamesListDialog: public QDialog
{
	Q_OBJECT

public:
	explicit GamesListDialog(QWidget *parent = nullptr);
	~GamesListDialog();

public slots:
	void addGameClicked();
	void removeGameClicked();
	void saveSettings();

protected:
	void addRow(const QString &name, const QString &path);

private:
	Ui::SettingsDialog *ui = nullptr;
};

