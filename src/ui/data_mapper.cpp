#include "data_mapper.hpp"
#include "selector_button.hpp"

#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QDataWidgetMapper>
#include <QItemDelegate>

QByteArray DataMapper::textProp = "text";
QByteArray DataMapper::indexProp = "currentIndex";
QByteArray DataMapper::valueProp = "value";
QByteArray DataMapper::idProp = "id";
QByteArray DataMapper::plainTextProp = "plainText";
QByteArray DataMapper::checkedProp = "checked";

void DataMapper::addWidgets(std::initializer_list<Params> params)
{
	for (Params param: params)
	{
		if (qobject_cast<QComboBox *>(param.widget))
			addMapping(param.widget, param.type, indexProp);

		else if (qobject_cast<SelectorButton *>(param.widget))
			addMapping(param.widget, param.type, idProp);

		else if (qobject_cast<QLineEdit *>(param.widget))
			addMapping(param.widget, param.type, textProp);

		else if (qobject_cast<QSpinBox *>(param.widget))
			addMapping(param.widget, param.type, valueProp);

		else if (qobject_cast<QLabel *>(param.widget))
			addMapping(param.widget, param.type, textProp);

		else if (qobject_cast<QPlainTextEdit *>(param.widget))
			addMapping(param.widget, param.type, plainTextProp);

		else if (qobject_cast<QCheckBox *>(param.widget))
			addMapping(param.widget, param.type, checkedProp);

		else
		{
			addMapping(param.widget, param.type);
			qDebug() << param.widget->metaObject()->className()
					 << "is not supported in DataMapper::addWidgets";
		}
	}
}
