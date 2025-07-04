#pragma once
#include <QWidget>

namespace Ui { class ItemsTab; }

class QMenu;
class DataMapper;
class ItemsModel;
class ItemEffectsModel;

class ItemsTab: public QWidget
{
	Q_OBJECT

public:
	explicit ItemsTab(QWidget *parent = nullptr);
	~ItemsTab();

	void init();

signals:
	void selectCommonEvent(int eventId);

private slots:
	void itemRowSelected(int row);
	void itemDamageTypeChanged(int index);

	void contextMenuRequested(const QPoint &pos);
	void actionEffectNewTriggered(bool);
	void actionEffectEditTriggered(bool);
	void actionEffectDeleteTriggered(bool);
	void actionEffectGotToTriggered(bool);

	void enableGroupBoxes(bool enabled);

	void itemNewClicked();
	void itemResizeClicked();
	void itemClearClicked();

private:
	Ui::ItemsTab *ui = nullptr;
	QMenu *itemEffectsListMenu = nullptr;
	ItemsModel *model = nullptr;
	ItemEffectsModel *effectsModel = nullptr;
	DataMapper *mapper = nullptr;
};

