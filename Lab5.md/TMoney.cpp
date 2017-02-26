#include <iostream>
#include "TMoney.h"

TMoney::TMoney()
{
	First = 0;
	Second = 0;
}

TMoney::TMoney(TMoney& money)
{
	First = money.First;
	Second = money.Second;
}

TMoney::TMoney(int ruble, int penny)
{
	First = ruble;
	if (penny > 99)
	{
		First += penny / 100;
		Second = 100 * ruble + penny - 100 * First;
	}
	else Second = penny;
}

void TMoney::operator () (int ruble, int penny)
{
	First = ruble;
	if (penny > 99)
	{
		First += penny / 100;
		Second = 100 * ruble + penny - 100 * First;
	}
	else Second = penny;
}

TMoney& TMoney::operator / (int number)
{
	if (number == 0) return (*this);
	int penny = 100 * First + Second;
	First = static_cast<double>(penny / (100 * number));
	Second = static_cast<double>(penny / number - 100 * First);
	return (*this);
}

TMoney TMoney::operator + (const TMoney& money)
{
	TMoney moneybuf;
	int penny = 100 * (money.First + First) + money.Second + Second;
	moneybuf.First = static_cast<double>(penny / 100);
	moneybuf.Second = static_cast<double>(penny - 100 * moneybuf.First);
	return moneybuf;
}

TMoney operator - (const TMoney& money1, const TMoney& money2)
{
	TMoney bufmoney1(money1.First, money1.Second);
	TMoney bufmoney2(money2.First, money2.Second);
	return (bufmoney1 + bufmoney2 / -1);
}

std::ostream& operator << (std::ostream& out, const TMoney& money)
{
	out << "Ruble is " << money.First
		<< " Penny is " << money.Second
		<< "\n";
	return out;
}
