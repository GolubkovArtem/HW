#include <iostream>
#include <string>
#include "Worker.h"

int main()
{
	int number(0);
	std::cout << "Enter the number:" << std::endl;
	std::cin >> number;
	Worker* worker = new Worker[number];
	std::string str;
	size_t scale(0);
	float increment(0);
	int i(number);
	while (i > 0)
	{
		i--;
		std::cout << "Enter the FIO:" << std::endl;
		std::cin >> str;
		std::cout << "Enter the scale:" << std::endl;
		std::cin >> scale;
		std::cout << "Enter the increment:" << std::endl;
		std::cin >> increment;
		worker[i].Init(str, scale, increment);
	}
	long float salarysumm(0);
	while (number > 0)
	{
		number--;
		worker[number].Show();
		salarysumm += worker[number].SalaryCalc();
	}
	std::cout << "Salarysumm is " << salarysumm << std::endl;
	system("pause");
}
