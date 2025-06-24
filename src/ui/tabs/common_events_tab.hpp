#pragma once
#include <QWidget>

namespace Ui { class CommonEventsTab; }

class QMenu;
class CommonEventsModel;
class DataMapper;
struct Event;

class CommonEventsTab: public QWidget
{
	Q_OBJECT

public:
	explicit CommonEventsTab(QWidget *parent = nullptr);
	~CommonEventsTab();

	void init();

private slots:
	void eventRowSelected(int row);
	void contextMenuRequested(const QPoint &pos);
	void applyButtonClicked();

private:
	Ui::CommonEventsTab *ui = nullptr;
	QMenu *contextMenu = nullptr;
	Event *currentEvent = nullptr;
	CommonEventsModel *model = nullptr;
	DataMapper *mapper = nullptr;
};

