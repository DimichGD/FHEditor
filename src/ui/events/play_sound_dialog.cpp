#include "play_sound_dialog.hpp"
#include "command_250.hpp"
#include "ui_play_sound_dialog.h"
#include "settings.hpp"
#include "event.hpp"

#include <QDir>

PlaySoundDialog::PlaySoundDialog(bool editing, QModelIndex index, QWidget *parent)
	: QDialog(parent), ui(new Ui::PlaySoundDialog)
{
	ui->setupUi(this);

	QDir seDir(Settings::Get()->lastPath + "/audio/se");
	QStringList stringList = seDir.entryList({ "*.rpgmvo", "*.ogg" }, QDir::Files | QDir::NoDotAndDotDot);
	model = new QStandardItemModel(stringList.size() + 1, 1, ui->listView);
	model->setItem(0, new QStandardItem("None"));

	int row = 1;
	int selectedRow = -1;
	QString expectedString;
	if (editing)
	{
		Command::It command = index.data(Qt::UserRole + 1).value<Command::It>();
		auto params = command->parameters.staticCast<Command_250>();
		expectedString = params->sound.name;
		ui->volumeSlider->setValue(params->sound.volume);
		ui->volumeSpinBox->setValue(params->sound.volume);
		ui->pitchSlider->setValue(params->sound.pitch);
		ui->pitchSpinBox->setValue(params->sound.pitch);
		ui->panSlider->setValue(params->sound.pan);
		ui->panSpinBox->setValue(params->sound.pan);
	}

	for (const QString &name: std::as_const(stringList))
	{
		QString nameWithoutExt = name.chopped(name.size() - name.lastIndexOf('.'));
		if (editing && nameWithoutExt == expectedString)
			selectedRow = row;

		model->setItem(row++, new QStandardItem(nameWithoutExt));
	}

	ui->listView->setModel(model);
	if (selectedRow != -1)
		ui->listView->setCurrentIndex(model->index(selectedRow, 0));
}

PlaySoundDialog::~PlaySoundDialog()
{
	delete ui;
}
