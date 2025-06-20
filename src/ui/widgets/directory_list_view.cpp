#include "directory_list_view.hpp"
#include "settings.hpp"

void DirectoryListView::setMode(PickerType type, QString itemName)
{
	switch (type)
	{
		case ICON_SET: hide(); return;
		case FACE: dir = QDir(Settings::Get()->lastPath + "/img/faces"); break;
		case ACTOR: dir = QDir(Settings::Get()->lastPath + "/img/sv_actors"); break;
		case ENEMY: dir = QDir(Settings::Get()->lastPath + "/img/sv_enemies"); break;
		case BATTLE_BACK_1: dir = QDir(Settings::Get()->lastPath + "/img/battlebacks1"); break;
		case BATTLE_BACK_2: dir = QDir(Settings::Get()->lastPath + "/img/battlebacks2"); break;
		case PARALLAX: dir = QDir(Settings::Get()->lastPath + "/img/parallaxes"); break;
		case CHARACTER: dir = QDir(Settings::Get()->lastPath + "/img/characters"); break;
		case TILESET: dir = QDir(Settings::Get()->lastPath + "/img/tilesets"); break;
		case MOVIE: dir = QDir(Settings::Get()->lastPath + "/movies"); break;
		case BGM: dir = QDir(Settings::Get()->lastPath + "/audio/bgm"); break;
		case BGS: dir = QDir(Settings::Get()->lastPath + "/audio/bgs"); break;
		case ME: dir = QDir(Settings::Get()->lastPath + "/audio/me"); break;
		case SE: dir = QDir(Settings::Get()->lastPath + "/audio/se"); break;
	}

	QStringList filterList;
	if (type >= FACE && type <= TILESET)
		filterList = { "*.rpgmvp", "*.png" };

	else if (type >= BGM && type <= SE)
		filterList = { "*.rpgmvo", "*.ogg" };

	else
		filterList = { "*.webm", "*.mp4" };

	QStringList stringList = dir.entryList(filterList, QDir::Files | QDir::NoDotAndDotDot);
	QStandardItemModel *model = new QStandardItemModel(stringList.size() + 1, 1, this);
	model->setItem(0, new QStandardItem("None"));

	int row = 1;
	int selectedRow = 0;
	for (const QString &name: std::as_const(stringList))
	{
		QString nameWithoutExt = name.chopped(name.size() - name.lastIndexOf('.'));
		if (nameWithoutExt == itemName)
			selectedRow = row;

		model->setItem(row++, new QStandardItem(nameWithoutExt));
	}

	setModel(model);
	setCurrentIndex(model->index(selectedRow, 0));
}

