#include "Chart.h"
#pragma once
class CircleChart : public Chart
{
public:
#pragma region Методы
	double f(double value);
#pragma endregion

#pragma region Конструкторы/Деструкторы
	CircleChart() {}
	CircleChart(string _name)
	{
		title = _name;
	}
	CircleChart(string _name, bool _mirror)
	{
		title = _name;
		mirror = _mirror;
	}
	~CircleChart() {};
#pragma endregion

};

