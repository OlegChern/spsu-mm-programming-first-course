#include "libs.h"
#include "Point.h"
#pragma once
class Chart
{
public:
#pragma region ����
	/// <summary>
	/// ��� �������
	/// </summary>
	string title;
	/// <summary>
	/// �������� �� �
	/// </summary>
	bool mirror;
#pragma endregion

#pragma region ������
	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	virtual double f(double value);
	/// <summary>
	/// �������� ����� Y ��� ��������� �������
	/// </summary>
	/// <param name="values">�������� X</param>
	/// <param name="mirror">�������� ������ �� ��� Y</param>
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
#pragma region ������������/�����������
	/// <summary>
	/// ����������� �� ���������
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

