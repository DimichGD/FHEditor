#pragma once
#include <QDataWidgetMapper>

class DataMapper: public QDataWidgetMapper
{
public:
	struct Params
	{
		QWidget *widget;
		int type;
	};

	explicit DataMapper(QObject *parent = nullptr): QDataWidgetMapper(parent) {}
	void addWidgets(std::initializer_list<Params> params);

private:
	static QByteArray textProp;
	static QByteArray indexProp;
	static QByteArray valueProp;
	static QByteArray idProp;
	static QByteArray plainTextProp;
	static QByteArray checkedProp;
};
