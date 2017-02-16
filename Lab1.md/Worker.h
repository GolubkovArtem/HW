#include <iostream>
#include <string>

class Worker
{
private:
	char* FIO;
	size_t Scale;
	float Increment;
public:
	~Worker();
	Worker();
	void Init(const std::string fio, size_t scale, float increment);
	void Show() const;
	long float SalaryCalc() const;
};
