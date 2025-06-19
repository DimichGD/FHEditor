#pragma once
#include "command_dialog.hpp"
#include "command_sound.hpp"

#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QDir>

namespace Ui { class PlaySoundDialog; }

class PlaySoundDialog : public CommandDialog
{
	Q_OBJECT

public:
	/*enum Type
	{
		BGM, BGS, ME, SE,
	};*/

	explicit PlaySoundDialog(CommandSound::Type type, bool editing, QModelIndex index, QWidget *parent = nullptr);
	~PlaySoundDialog();

	std::list<Command> resultCommands() override;

protected:
	void playButtonClicked();
	void stopButtonClicked();

private:
	Ui::PlaySoundDialog *ui = nullptr;
	QStandardItemModel *model = nullptr;

	int indent = 0;
	CommandSound::Type type;

	QMediaPlayer *mediaPlayer = nullptr;
	QAudioOutput *audioOutput = nullptr;
	QDir dir;
};

