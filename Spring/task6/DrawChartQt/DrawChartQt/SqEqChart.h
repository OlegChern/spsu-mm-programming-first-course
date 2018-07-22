#include "libs.h"
#include "Chart.h"
#pragma once
class SqEqChart :public Chart
{
public:
#pragma region ������������/�����������
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

#pragma region ������
	double f(double value);
#pragma endregion

};