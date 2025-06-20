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

	QPalette pal = app.palette();
	pal.setColor(QPalette::Base, QColor::fromRgb(255, 255, 255));
	pal.setColor(QPalette::AlternateBase, QColor::fromRgb(228, 236, 241));
	pal.setColor(QPalette::Inactive, QPalette::Highlight,
				 pal.color(QPalette::Active, QPalette::Highlight));
	pal.setColor(QPalette::Inactive, QPalette::HighlightedText,
				 pal.color(QPalette::Active, QPalette::HighlightedText));
	app.setPalette(pal);

	MainWindow wnd;
	wnd.show();
	return app.exec();
}
