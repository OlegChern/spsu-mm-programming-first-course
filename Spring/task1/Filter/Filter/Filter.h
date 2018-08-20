#pragma once


class Filter {
public:
	virtual void run(RGB** rgb, int width, int height) = 0;
	static char doubleToChar(double value)
	{
		if (value > 255)
		{
			return (char)255;
		}
		if (value < 0)
		{
			return (char)0;
		}
		return (char)value;
	}
};