#include "main_window.hpp"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	//app.setStyle(QStyleFactory::create("Fusion"));
	//qDebug() << QStyleFactory::keys();
	MainWindow wnd;
	wnd.show();
	return app.exec();
}
