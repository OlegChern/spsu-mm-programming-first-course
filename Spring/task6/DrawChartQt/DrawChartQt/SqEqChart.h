#include "libs.h"
#include "Chart.h"
#pragma once
class SqEqChart :public Chart
{
public:
#pragma region Конструкторы/Деструкторы
	SqEqChart(string _name)
	{
		title = _name;
	}
	SqEqChart(string _name, bool _mirror)
	{
		title = _name;
		mirror = _mirror;
	}
	SqEqChart();
	~SqEqChart();
#pragma endregion

#pragma region Методы
	double f(double value);
#pragma endregion

};