#pragma once
class Point
{
public:
#pragma region ����
	double X;
	double Y;
#pragma endregion

#pragma region ������
	void Move(double x, double y)
	{
		X += x;
		Y += y;
	}

	void InverseY()
	{
		Y *= -1;
	}

	void InverseX()
	{
		X *= -1;
	}

	void Scale(double scale) {
		X *= scale;
		Y *= scale;
	}
#pragma endregion

#pragma region ������������/�����������
	Point(double x, double y) {
		X = x;
		Y = y;
	}
	Point();
	~Point();
#pragma endregion

};

