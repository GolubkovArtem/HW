#include <iostream>
#include <string>
#include "TWorker.h"

int main()
{
	int number(12);
	std::cout << "Enter the number of workers:" << std::endl;
	std::cin >> number;
	TWorker* worker = new TWorker[number];
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
	double salarysumm(0);
	while (number > 0)
	{
		number--;
		std::cout << worker[number];
		salarysumm += worker[number].SalaryCalc();
	}
	std::cout << "Salarysumm is " << salarysumm << std::endl;
	delete[] worker;
	system("pause");
}
