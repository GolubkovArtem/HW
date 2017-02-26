#include <iostream>
#include "TMoney.h"

int main()
{
	TPair pair1(5, 12);
	std::cout << pair1;

	pair1(7, 13);
	std::cout << pair1;

	TPair pair2(8, 97);
	TPair pair3 = pair1 + pair2;
	std::cout << pair3;

	TMoney money1(4, 5);
	std::cout << money1;

	money1(2, 3);
	std::cout << money1;

	TMoney money2(10, 98);
	TMoney money3 = money1 + money2;
	std::cout << money3;

	money3 = money3 - money1;
	std::cout << money3;

	std::cout << money3 / 7;

	TPair* pair4 = &money3;
	(*pair4)(10, 111);
	std::cout << *pair4;

	system("pause");
}
