#include <iostream>
#include "TPair.h"

TPair::TPair()
{
	First = 0;
	Second = 0;
}

TPair::TPair(const TPair& pair)
{
	First = pair.First;
	Second = pair.Second;
}

TPair::TPair(int first, int second)
{
	First = first;
	Second = second;
}

void TPair::operator () (int first, int second)
{
	First = first;
	Second = second;
}

TPair& TPair::operator = (const TPair& pair)
{
	First = pair.First;
	Second = pair.Second;
	return (*this);
}

TPair TPair::operator + (const TPair& pair)
{
	TPair pairbuf;
	pairbuf.First = pair.First + First;
	pairbuf.Second = pair.Second + Second;
	return pairbuf;
}

std::ostream& operator << (std::ostream& out, const TPair& pair)
{
	out << "Firts is " << pair.First
		<< " Second is " << pair.Second
		<< "\n";
	return out;
}
