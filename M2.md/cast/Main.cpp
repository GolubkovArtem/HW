#include "TCastException.h"


template<class T>
T fromString(const char * data)
{

	if (data == nullptr) return 0;


	size_t length = strlen(data);
	bool minus(0);
	if (data[0] == '-') minus = 1;
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


	T result(0);
	for (int j = minus; j < length; j++)
	{
		if (j < dot)
			result += pow(10, dot - j - 1) * (data[j] - '0');
		else if (j > dot)
		{
			T t = pow(10, dot - j) * (data[j] - '0');
			result += t;
		}
		if (result < 0)
			throw(TOverFlow());
	}


	if (minus)
		return -result;
	else
		return result;
}
