#include "libs.h"
#include "Point.h"
#pragma once
class Chart
{
public:
#pragma region Поля
	/// <summary>
	/// имя графика
	/// </summary>
	string title;
	/// <summary>
	/// отражать по Х
	/// </summary>
	bool mirror;
#pragma endregion

#pragma region Методы
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	virtual double f(double value);
	/// <summary>
	/// получает точки Y для отрисовки графика
	/// </summary>
	/// <param name="values">значения X</param>
	/// <param name="mirror">отражать график по оси Y</param>
	/// <returns></returns>
	vector<Point> GetPoints(vector<double> values)
	{
		if (mirror)
		{
			vector<Point> points = vector<Point>();
			for (int i = 0; i < values.size(); i++)
				points.push_back(Point(values[i], f(values[i])));
			for (int i = values.size() - 1; i > -1; i--)
				points.push_back(Point(values[i], -f(values[i])));
			return points;
		}
		else
		{
			vector<Point> points = vector<Point>();
			for each(double item in values)
				points.push_back(Point(item, f(item)));
			return points;
		}
	}
#pragma endregion

public:
#pragma region Конструкторы/Деструкторы
	/// <summary>
	/// конструктор по умолчанию
	/// </summary>
	Chart()
	{
		mirror = false;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_name"></param>
	Chart(string _name)
	{
		title = _name;
		mirror = false;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="_name"></param>
	/// <param name="_mirror"></param>
	Chart(string _name, bool _mirror)
	{
		title = _name;
		mirror = _mirror;
	}
	~Chart() {};
#pragma endregion
};

