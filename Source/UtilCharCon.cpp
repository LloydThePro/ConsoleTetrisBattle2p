#include "UtilityCharConverter.h"
void FloatToStr(char * chr, const float& n)
{
	int temp = (int)n;
	float floater = n - temp;
	int c = temp, index = 0;
	while (c > 0)
	{
		c /= 10;
		index++;
	}
	int values[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < index; i++)
	{
		values[i] = temp % 10;
		temp /= 10;
	}

	for (int i = 0; i < index; i++)
	{
		chr[i] = IntToChar(values[index - i - 1]);
	}
	chr[index] = '.';

	int fvalues[3] = { 0,0,0 };
	int ftemp = floater * 1000;

	for (int i = 0; i < 3; i++)
	{
		fvalues[i] = ftemp % 10;
		ftemp /= 10;
		if (fvalues[i] != 0)
			chr[index + 3 - i] = IntToChar(fvalues[i]);
		else
			chr[index + 3 - i] = 0;
	}
}
void FloatToStr(char * chr, const double& n)
{
	int temp = (int)n;
	float floater = n - temp;
	int c = temp, index = 0;
	while (c > 0)
	{
		c /= 10;
		index++;
	}
	int values[10] = { 0,0,0,0,0,0,0,0,0,0 };
	for (int i = 0; i < index; i++)
	{
		values[i] = temp % 10;
		temp /= 10;
	}

	for (int i = 0; i < index; i++)
	{
		chr[i] = IntToChar(values[index - i - 1]);
	}
	chr[index] = '.';

	int fvalues[3] = { 0,0,0 };
	int ftemp = floater * 1000;

	for (int i = 0; i < 3; i++)
	{
		fvalues[i] = ftemp % 10;
		ftemp /= 10;
		if (fvalues[i] != 0)
			chr[index + 3 - i] = IntToChar(fvalues[i]);
		else
			chr[index + 3 - i] = 0;
	}
}

void IntToStr(char * cptr, int n)
{
	int c = n;
	int a = 0;
	while (c > 0)
	{
		c /= 10;
		a++;
	}
	int values[10] = { 0,0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < a; i++)
	{
		values[i] = n % 10;
		n /= 10;
	}

	for (int i = 0; i < a; i++)
	{
		cptr[i] = IntToChar(values[a - i - 1]);
	}

	cptr[a] = 0;


}

void IntToStr(std::string& cptr, int n)
{

	int c = n;
	int a = 0;
	while (c > 0)
	{
		c /= 10;
		a++;
	}

	int values[10] = { 0,0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < a; i++)
	{
		values[i] = n % 10;
		n /= 10;
	}

	for (int i = 0; i < a; i++)
	{
		cptr[i] = IntToChar(values[a - i - 1]);
	}

	cptr[a] = 0;


}

int CharToInt(const char& a)
{
	int b = 0;
	for (int i = 48; i < 58; i++)
	{
		if (i == (int)a)
		{
			return b;
		}
		b++;
	}
	return 0;
}

char IntToChar(const int& a)
{
	switch (a)
	{
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	case 0:
		return '0';
		break;
	default:
		return '0';
		break;
	}
	return '0';
}