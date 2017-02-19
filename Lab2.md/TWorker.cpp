#include <iostream>
#include <string>
#include "TWorker.h"

TWorker::~TWorker()
{
	delete[] FIO;
}

TWorker::TWorker()
{
	FIO = new char[1];
	FIO[0] = '\0';
	Scale = 0;
	Increment = 0;
}

TWorker::TWorker(const TWorker& worker)
{
	int i(0);
	while (worker.FIO[i] != '\0') i++;
	FIO = new char[i + 1];
	memcpy(FIO, worker.FIO, (i + 1) * sizeof(char));
	Scale = worker.Scale;
	Increment = worker.Increment;
}

void TWorker::Init(const std::string fio, size_t scale, float increment)
{
	delete[] FIO;
	int i(0);
	while (fio[i] != '\0') i++;
	FIO = new char[i + 1];
	for (i = 0; fio[i] != '\0'; i++) FIO[i] = fio[i];
	FIO[i] = '\0';
	Scale = scale;
	Increment = increment;
}

double TWorker::SalaryCalc() const
{
	return (Scale + Scale * Increment);
}

std::ostream & operator<<(std::ostream &out, const TWorker &worker)
{
	std::cout << "FIO is "
		<< worker.FIO
		<< " Sclale is "
		<< worker.Scale
		<< " Increment is "
		<< worker.Increment
		<< std::endl;
	return out;
}
