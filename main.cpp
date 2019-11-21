
#include <QApplication>

#include "view/mainwindow.h"
#include "utils/logger.h"

int main(int argc, char *argv[]) {

	Logger::getInstance().setLogFile("QtWinNetworkManager.log");
	Logger::getInstance().setLogLevel(Logger::LEVEL_DEBUG);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
