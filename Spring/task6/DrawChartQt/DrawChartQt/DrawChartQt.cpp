#include "DrawChartQt.h"
#include "libs.h"
#include "Chart.h"
#include "CircleChart.h"
#include "SqEqChart.h"

CircleChart circleChart = CircleChart("Circle", true);
SqEqChart sqeqChart = SqEqChart("Parabolic", false);
vector<Point> _points;
DrawChartQt::DrawChartQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect
	(
		ui.comboBox,
		SIGNAL(currentIndexChanged(int)),
		this,
		SLOT(onSelectionChanged(int))
	);
	connect
	(
		ui.btnInc,
		SIGNAL(clicked()),
		this,
		SLOT(onInc())
	);
	connect
	(
		ui.btnDec,
		SIGNAL(clicked()),
		this,
		SLOT(onDec())
	);
	ui.comboBox->addItem(QString(circleChart.title.c_str()));
	ui.comboBox->addItem(QString(sqeqChart.title.c_str()));
}

vector<Point> DrawChartQt::Scale(vector<Point> points, double scale)
{
	for (int i = 0; i < points.size(); i++)
		points[i].Scale(scale);
	return points;
}

vector<Point> DrawChartQt::InvertY(vector<Point> points)
{
	for (int i = 0; i < points.size(); i++)
		points[i].InverseY();
	return points;
}

void DrawChartQt::Draw(vector<Point> points)
{
	points = InvertY(points);
	scene = new QGraphicsScene();
	ui.graphicsView->setScene(scene);
	ui.graphicsView->setRenderHint(QPainter::Antialiasing);
	ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene->setSceneRect(-250, -250, 500, 500);
	if (points.size() > 0)
		for (int i = 0; i < points.size() - 1; i++) {
			scene->addLine(
				points[i].X,
				points[i].Y,
				points[i + 1].X,
				points[i + 1].Y,
				QPen(Qt::black));
		}
}

void DrawChartQt::onInc()
{
	ui.label->setText("inc");
	_points = Scale(_points, 1.2);
	Draw(_points);
}

void DrawChartQt::onDec()
{
	ui.label->setText("dec");
	_points = Scale(_points, 0.8);
	Draw(_points);
}

vector<double> DrawChartQt::GetPoints(double start, double end, double step)
{
	vector<double> points;
	for (double i = min(start, end); i <= max(start, end); i += step)
		points.push_back(i);
	return points;
}

void DrawChartQt::onSelectionChanged(int index) {
	ui.label->setText(QString(to_string(index).c_str()));
	if (index > -1 && index < 2) {
		if (index == 0)
			_points = circleChart.GetPoints(GetPoints(-100, 100, 0.1));
		if (index == 1)
			_points = sqeqChart.GetPoints(GetPoints(-100, 100, 0.1));
		Draw(_points);
	}
}