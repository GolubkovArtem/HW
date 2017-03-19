#include "TCastException.h"


std::string TOverFlow::ErrorType = "OverFlow";
std::string TInvalidSymbol::ErrorType = "InvalidSymbol";


int IntFromString(const char * data)
{
	try
	{
		size_t length = strlen(data);
		if (length > 11) throw(TOverFlow());
		if (length == 0) return 0;
		int digit = 10;
		bool minus(0);
		if (data[0] == '-') minus = 1;
		for (size_t i = minus; i < length; ++i)
		{
			if (isalnum(data[i]))
			{
				if (isalpha(data[i]) && 0 <= toupper(data[i]) - 'A' && toupper(data[i]) - 'A' <= 5) digit = 16;
				else
				{
					if (isalpha(data[i]))
					{
						throw(TInvalidSymbol());
					}
				}
			}
			else
					throw(TInvalidSymbol());
		}
		long long int buf(0);
		for (int i = length - 1; i >= minus; --i)
		{
			if (isdigit(data[i]))
				buf += pow(digit, length - 1 - i) * (data[i] - '0');
			else
				buf += pow(digit, length - 1 - i) * (toupper(data[i]) - 'A' + 10);
		}
		if (buf <= pow(2, 31) && !minus)
		{
			return buf;
		}
		else if (buf <= pow(2, 31) - 1)
		{
			return -buf;
		}
		throw(TOverFlow());
	}
	catch(...)
	{
		throw;
	}
}


float FloatFromString(const char * data)
{
	try
	{
		size_t length = strlen(data);
		bool minus(0);
		if (data[0] == '-') minus = 1;
		size_t i(minus);
		int dot(-1);
		for (; i < length; ++i)
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
	catch(...)
	{
		throw;
	}
}


bool BoolFromString(const char * data)
{
	if (!strlen(data)) return 0;
	for (int i = 0; i < strlen(data); ++i)
	{
		if (!isprint(data[i]))
			throw(TInvalidSymbol());
	}
	return 1;
}



int main()
{
	try
	{
		std::cout << IntFromString("12343") << std::endl;
		std::cout << IntFromString("2147483648") << std::endl;
		std::cout << IntFromString("-2147483647") << std::endl;
		std::cout << IntFromString("-2147483648") << std::endl;
	}
	catch (TOverFlow error)
	{
		std::cout << error.what() << "\n\n";
	}
	catch (TInvalidSymbol error)
	{
		std::cout << error.what() << "\n\n";
	}

	try
	{
		std::cout << IntFromString("aA") << std::endl;
		std::cout << IntFromString("-aBcdd") << std::endl;
		std::cout << IntFromString("AAAAAAAAAAA") << std::endl;
	}
	catch (TOverFlow error)
	{
		std::cout << error.what() << "\n\n";
	}
	catch (TInvalidSymbol error)
	{
		std::cout << error.what() << "\n\n";
	}


	try
	{
		std::cout << FloatFromString("12.343") << std::endl;
		std::cout << FloatFromString("-12.343") << std::endl;
		std::cout << FloatFromString(".343") << std::endl;
		std::cout << FloatFromString("12.3b43") << std::endl;
	}
	catch (TOverFlow error)
	{
		std::cout << error.what() << "\n\n";
	}
	catch (TInvalidSymbol error)
	{
		std::cout << error.what() << "\n\n";
	}


	try
	{
		std::cout << FloatFromString("-123456789012345678901234567890123456789.") << std::endl;
		std::cout << FloatFromString("-.00000000000000000000000000000000000001") << std::endl;
		std::cout << FloatFromString("-.000000000000000000000000000000000000001") << std::endl;
	}
	catch (TOverFlow error)
	{
		std::cout << error.what() << "\n\n";
	}
	catch (TInvalidSymbol error)
	{
		std::cout << error.what() << "\n\n";
	}


	try
	{
		std::cout << BoolFromString("qwerty123") << std::endl;
		std::cout << BoolFromString("") << std::endl;
		std::cout << BoolFromString(" ") << std::endl;
		std::cout << BoolFromString("\n") << std::endl;
	}
	catch (TInvalidSymbol error)
	{
		std::cout << error.what() << "\n\n";
	}

	system("pause");
}
