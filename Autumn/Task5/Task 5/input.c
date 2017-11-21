#include "math.h"

char inputString(char* s)
{
	char* c = s;
	int error = 0;
	int nSigned = 0;
	int nFloat = 0;
	int nStart = 1;
	while (*c != 0)
	{
		if (nStart == 1)
		{
			switch ((int)*c)
			{
			case 45:
			{
				nSigned++;
				if (((int)*(c + 1) == 48) && ((int)*(c + 2) != 46))
				{
					error++;
				}
				break;
			}
			case 48:
			{
				if ((int)*(c + 1) != 46)
				{
					error++;
				}
				break;
			}
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
			{
				break;
			}
			default:
			{
				error++;
				break;
			}
			}
			nStart--;
		}
		else
		{
			switch ((int)*c)
			{
				case 46:
				{
					if ((nFloat == 0) && (*(c + 1) != 0))
					{
						nFloat++;
					}
					else
					{
						error++;
					}
				}
				case 48:
				case 49:
				case 50:
				case 51:
				case 52:
				case 53:
				case 54:
				case 55:
				case 56:
				case 57:
				{
					break;
				}
				default:
				{
					error++;
					break;
				}
			}
		}
		c++;
	}
	if (error > 0)
	{
		return 'e';
	}
	else
	{
		if (nSigned > 0)
		{
			return 's';
		}
		else
		{
			if (nFloat > 0)
			{
				return 'f';
			}
			else
			{
				return 'u';
			}
		}
	}
}