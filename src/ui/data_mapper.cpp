#include "data_mapper.hpp"
#include "selector_button.hpp"
#include "icon_widget.hpp"

#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QCheckBox>


DataMapper::DataMapper(QAbstractItemModel *sourceModel, QObject *parent): QObject(parent)
{
	model = sourceModel;
	connect(sourceModel, &QAbstractItemModel::dataChanged, this, &DataMapper::dataChanged);
}

void DataMapper::setCurrentIndex(int index)
{
	if (!model)
	{
		qDebug() << "DataMapper::setCurrentIndex model is not set";
		return;
	}

	modelWriteBlocked = true;
	currentIndex = index;

	if (index < 0)
		for (auto &entry: widgetMap)
			entry.widget->setProperty(entry.property, QVariant());

	else
		for (auto &entry: widgetMap)
			entry.widget->setProperty(entry.property, model->data(model->index(currentIndex, entry.section), Qt::EditRole));

	modelWriteBlocked = false;
}

void DataMapper::add(QLineEdit *widget, int section)
{
	widgetMap.emplace_back(widget, section, "text");
	connect(widget, &QLineEdit::textChanged, this,
			[widget, this](const QString &text) { widgetDataChanged(widget, text); });
}

void DataMapper::add(QPlainTextEdit *widget, int section)
{
	widgetMap.emplace_back(widget, section, "plainText");
	connect(widget, &QPlainTextEdit::textChanged, this, [widget, this]()
	{
		QPlainTextEdit *textEdit = static_cast<QPlainTextEdit *>(widget);
		widgetDataChanged(textEdit, textEdit->toPlainText());
	});
	//connect(widget, &QObject::destroyed, this, &DataMapper2::widgetDestroyed);
}

void DataMapper::add(QSpinBox *widget, int section)
{
	widgetMap.emplace_back(widget, section, "value");
	connect(widget, &QSpinBox::valueChanged, this,
			[widget, this](int value) { widgetDataChanged(widget, value); });
	//connect(widget, &QSpinBox::valueChanged, this, &DataMapper2::widgetIntDataChanged);
}

void DataMapper::add(QComboBox *widget, int section)
{
	widgetMap.emplace_back(widget, section, "currentIndex");
	connect(widget, &QComboBox::activated, this,
			[widget, this](int value) { widgetDataChanged(widget, value); });
	//connect(widget, &QComboBox::currentIndexChanged, this, &DataMapper2::widgetIntDataChanged);
}

void DataMapper::add(QCheckBox *widget, int section)
{
	widgetMap.emplace_back(widget, section, "checked");
	connect(widget, &QCheckBox::toggled, this,
			[widget, this](bool value) { widgetDataChanged(widget, value); });
}

void DataMapper::add(IconWidget *widget, int section)
{
	widgetMap.emplace_back(widget, section, "iconIndex");
	connect(widget, &IconWidget::iconChanged, this,
			[widget, this](int value) { widgetDataChanged(widget, value); });
}

void DataMapper::add(SelectorButton *widget, int section)
{
	widgetMap.emplace_back(widget, section, "id");
	connect(widget, &SelectorButton::idChanged, this,
			[widget, this](int value) { widgetDataChanged(widget, value); });
}

void DataMapper::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
	if (currentIndex < 0)
		return;

	if (!roles.contains(Qt::EditRole))
		return;

	if (currentIndex < topLeft.row() || currentIndex > bottomRight.row())
		return;

	modelWriteBlocked = true;

	for (auto &entry: widgetMap)
		if (entry.section >= topLeft.column() && entry.section <= bottomRight.column())
			entry.widget->setProperty(entry.property, model->data(model->index(currentIndex, entry.section), Qt::EditRole));

	modelWriteBlocked = false;
}

void DataMapper::widgetDataChanged(QObject *sender, QVariant data)
{
	if (currentIndex < 0)
		return;

	if (modelWriteBlocked)
		return;

	if (!model)
		return;

	for (auto &entry: widgetMap)
		if (entry.widget == sender)
			model->setData(model->index(currentIndex, entry.section), data, Qt::EditRole);
}

bool DataMapper::Predicate::operator()(const WidgetMapEntry &entry) const
{
	return object == entry.widget;
}


