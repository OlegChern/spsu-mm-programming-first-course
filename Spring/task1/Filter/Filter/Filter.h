#pragma once


class Filter {
public:
	virtual RGB** run(RGB** rgb, int width, int height) = 0;
	static unsigned char doubleToChar(double value)
	{
		if (value > 255)
		{
			return (unsigned char)255;
		}
		if (value < 0)
		{
			return (unsigned char)0;
		}
		return (unsigned char)value;
	}
};