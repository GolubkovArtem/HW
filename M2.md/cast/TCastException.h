#include <iostream>
#include <stdexcept>
#include <algorithm>


struct TCastException 
	: public std::exception
{
	TCastException() = default;
	TCastException(const char* const message)
		: std::exception(message)
	{ }
};


struct TOverFlow 
	: public TCastException
{
	TOverFlow() 
		: TCastException("OverFlow")
	{ }
};


struct TInvalidSymbol 
	: public TCastException
{
	TInvalidSymbol()
		: TCastException("InvalidSymbol")
	{ }
};


struct TInvalidNumber 
	: public TCastException
{
	TInvalidNumber()
		: TCastException("InvalidNumber")
	{ }
};
