#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>


class TCastException : private std::exception{
public:
	virtual std::string what() = 0;
};


class TOverFlow : public TCastException
{
	static std::string ErrorType;
public:
	std::string what()
	{
		return ErrorType;
	}
};


class TInvalidSymbol : public TCastException
{
	static std::string ErrorType;
public:
	std::string what()
	{
		return ErrorType;
	}
};
