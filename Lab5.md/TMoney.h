#include <iostream>
#include "TPair.h"

class TMoney :public TPair
{
public:
	TMoney();
	TMoney(TMoney& money);
	TMoney(int ruble, int penny);
	void operator () (int ruble, int penny);
	TMoney& operator / (int number);
	TMoney operator + (const TMoney& money);
	friend std::ostream& operator << (std::ostream& , const TMoney&);
	friend TMoney operator - (const TMoney& , const TMoney& );
};

TMoney operator - (const TMoney& money1, const TMoney& money2);
std::ostream& operator << (std::ostream& out, const TMoney& money);
