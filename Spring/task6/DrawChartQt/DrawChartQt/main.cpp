#include "DrawChartQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DrawChartQt w;
	w.show();
	return a.exec();
}
