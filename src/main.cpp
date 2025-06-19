#include "main_window.hpp"

#include <QApplication>
#include <QStyleFactory>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setStyle(QStyleFactory::create("Fusion"));
	//qDebug() << QStyleFactory::keys();

	/*const QStringList fontFamilies = QFontDatabase::families();
	for (const QString &family: fontFamilies)
	{
		if (family.contains("Mono"))
			qDebug() << family;
	}*/

	//qDebug() << QFont().defaultFamily();
	//qDebug() << qApp->font().family();
	//qDebug() << QFontDatabase::systemFont(QFontDatabase::GeneralFont);
	//qDebug() << QFontDatabase::systemFont(QFontDatabase::FixedFont);

	MainWindow wnd;
	wnd.show();
	return app.exec();
}
