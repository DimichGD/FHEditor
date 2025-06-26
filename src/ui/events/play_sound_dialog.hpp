#pragma once
#include "command_dialog.hpp"
#include "command_sound.hpp"

namespace Ui { class PlaySoundDialog; }

class QMediaPlayer;
class QAudioOutput;

class PlaySoundDialog: public CommandDialog
{
	Q_OBJECT

public:
	explicit PlaySoundDialog(CommandSound::Type type, bool editing, QModelIndex index, QWidget *parent = nullptr);
	~PlaySoundDialog();

	std::list<Command> resultCommands() override;

protected:
	void playButtonClicked();
	void stopButtonClicked();

private:
	Ui::PlaySoundDialog *ui = nullptr;

	//int indent = 0;
	CommandSound::Type type;

	QMediaPlayer *mediaPlayer = nullptr;
	QAudioOutput *audioOutput = nullptr;
};

