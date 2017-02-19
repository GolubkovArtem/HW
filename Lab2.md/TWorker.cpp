#include <iostream>
#include <string>
#include "TWorker.h"

TWorker::~TWorker()
{}

TWorker::TWorker()
{
	FIO = '\0';
	Scale = 0;
	Increment = 0;
}

TWorker::TWorker(const TWorker& worker)
{
	FIO = worker.FIO;
	Scale = worker.Scale;
	Increment = worker.Increment;
}

void TWorker::Init(const std::string fio, size_t scale, float increment)
{
	FIO = fio;
	Scale = scale;
	Increment = increment;
}

double TWorker::SalaryCalc() const
{
	return (Scale + Scale * Increment);
}

std::ostream& operator << (std::ostream& out, const TWorker& worker)
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
