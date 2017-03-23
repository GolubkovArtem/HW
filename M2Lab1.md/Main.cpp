#include "TCastException.h"


int IntFromString(const char * data)
{	
	size_t length = strlen(data);
	bool minus(0);
	if (data[0] == '-') minus = 1;


	if (length == 0) return 0;
	if (strlen(data) > 11) throw(TOverFlow());
	if (length != 1 && data[minus] == '0')
		throw(TInvalidNumber());


	for (size_t i = minus; i < length; ++i)
	{
		if (!isdigit(data[i]))
			throw(TInvalidSymbol());
	}


	int buf(0);
	for (int i = minus; i < length; ++i)
	{
		buf -= pow(10, length - 1 - i) * (data[i] - '0');
		if (buf > 0)
			throw(TOverFlow());
	}


	if (minus)
		return buf;
	if (-buf >= 0)
		return -buf;
	throw(TOverFlow());
}


float FloatFromString(const char * data)
{
	bool minus(0);
	if (data[0] == '-') minus = 1;
	size_t length = strlen(data);
	int dot(-1);


	for (size_t i = minus; i < length; ++i)
	{
		if (data[i] == '.')
		{
			if (dot == -1)
			{
				dot = i;
				continue;
			}
			else
				throw(TInvalidSymbol());
		}
		if (!isdigit(data[i]))
			throw (TInvalidSymbol());
	}

	if (dot == -1) dot = length;
	if (dot - minus > 39 || length - dot > 39)
		throw (TOverFlow());


	float result(0);
	for (int j = minus; j < length; j++)
	{
		if (j < dot)
			result += pow(10, dot - j - 1) * (data[j] - '0');
		else if (j > dot)
		{
			float t = pow(10, dot - j) * (data[j] - '0');
			result += t;
		}
	}


	if (minus)
		return -result;
	else
		return result;
}


bool BoolFromString(const char * data)
{
	size_t length = strlen(data);
	if (!length || (length == 1 && *data == '0')) return 0;
	if (FloatFromString(data)) return 1;
}
