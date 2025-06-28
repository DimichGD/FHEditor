#pragma once
#include <QDataWidgetMapper>

class QLineEdit;
class QPlainTextEdit;
class QSpinBox;
class QComboBox;
class QCheckBox;
class SelectorButton;
class IconWidget;

class DataMapper: public QObject
{
	Q_OBJECT

public:
	DataMapper(QAbstractItemModel *sourceModel, QObject *parent = nullptr);

	void setCurrentIndex(int index);

	void add(QLineEdit *widget, int section);
	void add(QPlainTextEdit *widget, int section);
	void add(QSpinBox *widget, int section);
	void add(QComboBox *widget, int section);
	void add(QCheckBox *widget, int section);
	void add(IconWidget *widget, int section);
	void add(SelectorButton *widget, int section);

private slots:
	void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles);

private:
	void widgetDataChanged(QObject *sender, QVariant data);

private:
	struct WidgetMapEntry
	{
		QWidget *widget;
		int section;
		QByteArray property;
	};

	struct Predicate
	{
		QObject *object;
		bool operator()(const WidgetMapEntry &entry) const;
	};

	int currentIndex = -1;
	bool modelWriteBlocked = false;
	QAbstractItemModel *model = nullptr;
	std::vector<WidgetMapEntry> widgetMap;
};
