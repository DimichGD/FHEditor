#include "play_sound_dialog.hpp"
#include "command_250.hpp"
#include "command_factory.hpp"
#include "ui_play_sound_dialog.h"
#include "settings.hpp"
#include "event.hpp"

#include <QDir>
#include <QFile>
#include <QAudioOutput>

PlaySoundDialog::PlaySoundDialog(Type type, bool editing, QModelIndex index, QWidget *parent)
	: CommandDialog(parent), ui(new Ui::PlaySoundDialog)
{
	ui->setupUi(this);
	this->type = type;

	switch (type)
	{
		case BGM: dir = QDir(Settings::Get()->lastPath + "/audio/bgm"); break;
		case BGS: dir = QDir(Settings::Get()->lastPath + "/audio/bgs"); break;
		case ME: dir = QDir(Settings::Get()->lastPath + "/audio/me"); break;
		case SE: dir = QDir(Settings::Get()->lastPath + "/audio/se"); break;
	}

	QStringList stringList = dir.entryList({ "*.rpgmvo", "*.ogg" }, QDir::Files | QDir::NoDotAndDotDot);
	model = new QStandardItemModel(stringList.size() + 1, 1, ui->listView);
	model->setItem(0, new QStandardItem("None"));

	Command::It command = index.data(Qt::UserRole + 1).value<Command::It>();
	indent = command->indent;

	int row = 1;
	int selectedRow = -1;
	QString expectedString;
	if (editing)
	{
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

	connect(ui->playButton, &QPushButton::clicked, this, &PlaySoundDialog::playButtonClicked);
	connect(ui->stopButton, &QPushButton::clicked, this, &PlaySoundDialog::stopButtonClicked);

	mediaPlayer = new QMediaPlayer(this);
	audioOutput = new QAudioOutput(this);
	mediaPlayer->setAudioOutput(audioOutput);
}

PlaySoundDialog::~PlaySoundDialog()
{
	delete ui;
}

std::list<Command> PlaySoundDialog::resultCommands()
{
	std::list<Command> resultList;

	QString name = "None";
	if (ui->listView->currentIndex().row() != -1)
		name = ui->listView->currentIndex().data().toString();

	int volume = ui->volumeSlider->value();
	int pitch = ui->pitchSlider->value();
	int pan = ui->panSlider->value();
	auto rootParams = CommandFactory::createCommand<Command_250>(Sound { name, pan, pitch, volume });
	resultList.push_back({ CommandFactory::PLAY_SE, indent, rootParams });

	return resultList;
}

void PlaySoundDialog::playButtonClicked()
{
	if (!ui->listView->currentIndex().isValid())
		return;

	QUrl url = QUrl::fromLocalFile(dir.absolutePath()
				+ "/" + ui->listView->currentIndex().data().toString() + ".ogg");

	mediaPlayer->setSource(url);
	audioOutput->setVolume(0.5f);
	mediaPlayer->play();
}

void PlaySoundDialog::stopButtonClicked()
{
	mediaPlayer->stop();
}
