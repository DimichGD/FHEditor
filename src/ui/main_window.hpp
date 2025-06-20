#pragma once
#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void loadGame();

protected:
	void closeEvent(QCloseEvent *event) override;

private slots:
	void openSettingsDialog();

private:
	Ui::MainWindow *ui = nullptr;
};
