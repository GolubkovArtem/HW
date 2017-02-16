#include <iostream>
#include <string>
#include "Worker.h"

Worker::~Worker()
{
	delete[] FIO;
}

Worker::Worker()
{
	FIO = nullptr;
	Scale = 0;
	Increment = 0;
}

void Worker::Init(const std::string fio, size_t scale, float increment)
{
	if (FIO != nullptr) delete[] FIO;
	int i(0);
	while (fio[i] != '\0') i++;
	FIO = new char[i + 1];
	for (i = 0; fio[i] != '\0'; i++) FIO[i] = fio[i];
	FIO[i] = '\0';
	Scale = scale;
	Increment = increment;
}

void Worker::Show() const
{
	std::cout << "FIO is "
		<< FIO
		<< " Sclale is "
		<< Scale
		<< " Increment is "
		<< Increment
		<< std::endl;
}

long float Worker::SalaryCalc() const
{
	return (Scale + Scale * Increment);
}
