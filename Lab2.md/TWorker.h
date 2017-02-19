#include <iostream>
#include <string>

class TWorker
{
private:
	std::string FIO;
	size_t Scale;
	float Increment;
public:
	~TWorker();
	TWorker();
	TWorker(const TWorker& worker);
	void Init(const std::string fio, size_t scale, float increment);
	double SalaryCalc() const;
	friend std::ostream& operator << (std::ostream&, const TWorker&);
};

std::ostream& operator << (std::ostream& out, const TWorker& worker);
