#include "play_sound_dialog.hpp"
#include "command_sound.hpp"
#include "command_factory.hpp"
#include "ui_play_sound_dialog.h"
#include "event.hpp"

#include <QMediaPlayer>
#include <QAudioOutput>

PlaySoundDialog::PlaySoundDialog(CommandSound::Type type, bool editing, QModelIndex index, QWidget *parent)
	: CommandDialog(parent), ui(new Ui::PlaySoundDialog)
{
	ui->setupUi(this);
	this->type = type;

	Command::Iterator command = Command::iteratorFromIndex(index);
	indent = command->indent;

	QString expectedString;
	if (editing)
	{
		auto params = static_cast<CommandSound *>(command->parameters.get());
		expectedString = params->sound.name;
		ui->volumeSlider->setValue(params->sound.volume);
		ui->volumeSpinBox->setValue(params->sound.volume);
		ui->pitchSlider->setValue(params->sound.pitch);
		ui->pitchSpinBox->setValue(params->sound.pitch);
		ui->panSlider->setValue(params->sound.pan);
		ui->panSpinBox->setValue(params->sound.pan);
	}

	ui->listView->setMode(PickerType(type), expectedString);

	connect(ui->playButton, &QPushButton::clicked, this, &PlaySoundDialog::playButtonClicked);
	connect(ui->stopButton, &QPushButton::clicked, this, &PlaySoundDialog::stopButtonClicked);
	connect(ui->volumeSlider, &QSlider::sliderMoved, ui->volumeSpinBox, &QSpinBox::setValue);
	connect(ui->volumeSpinBox, &QSpinBox::valueChanged, ui->volumeSlider, &QSlider::setValue);
	connect(ui->pitchSlider, &QSlider::sliderMoved, ui->pitchSpinBox, &QSpinBox::setValue);
	connect(ui->pitchSpinBox, &QSpinBox::valueChanged, ui->pitchSlider, &QSlider::setValue);
	connect(ui->panSlider, &QSlider::sliderMoved, ui->panSpinBox, &QSpinBox::setValue);
	connect(ui->panSpinBox, &QSpinBox::valueChanged, ui->panSlider, &QSlider::setValue);

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
	Sound sound { name, pan, pitch, volume };

	auto rootParams = CommandFactory::createCommand<CommandSound>(type, sound);
	resultList.push_back({ CommandFactory::Code(type), indent, rootParams });

	return resultList;
}

void PlaySoundDialog::playButtonClicked()
{
	if (!ui->listView->currentIndex().isValid())
		return;

	if (ui->listView->currentIndex().row() == 0)
		return;

	QUrl url = QUrl::fromLocalFile(ui->listView->path()
					+ "/" + ui->listView->currentIndex().data().toString() + ".ogg");

	mediaPlayer->setSource(url);
	audioOutput->setVolume(ui->volumeSlider->value() * 0.01f);
	mediaPlayer->setPlaybackRate(ui->pitchSlider->value() * 0.01f);
	mediaPlayer->play();
}

void PlaySoundDialog::stopButtonClicked()
{
	mediaPlayer->stop();
}
