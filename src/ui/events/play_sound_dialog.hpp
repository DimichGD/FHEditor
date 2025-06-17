#pragma once

#include <QStandardItemModel>
#include <QDialog>

namespace Ui { class PlaySoundDialog; }

class PlaySoundDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PlaySoundDialog(bool editing, QModelIndex index, QWidget *parent = nullptr);
	~PlaySoundDialog();

private:
	Ui::PlaySoundDialog *ui = nullptr;
	QStandardItemModel *model = nullptr;
};

