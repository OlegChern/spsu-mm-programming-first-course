#include "libs.h"
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DrawChartQt.h"
#include "Point.h"
class DrawChartQt : public QMainWindow
{
	Q_OBJECT
private slots:
	void onSelectionChanged(int index);
	void onInc();
	void onDec();
public:
	DrawChartQt(QWidget *parent = Q_NULLPTR);
	vector<Point> Scale(vector<Point> points, double scale);
	vector<Point> InvertY(vector<Point> points);
	void Draw(vector<Point> points);
private:
	QGraphicsScene * scene;
	Ui::DrawChartQtClass ui;
	vector<double> GetPoints(double start, double end, double step);
};
