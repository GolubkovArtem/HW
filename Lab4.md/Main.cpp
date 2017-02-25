#include <iostream>
#include "TOrb.h"

int main()
{
	TCircle circle(2);
	std::cout << circle;
	TOrb orb(2);
	std::cout << orb;
	TCircle* orb1 = &orb;
	std::cout << *orb1;
	system("pause");
}
