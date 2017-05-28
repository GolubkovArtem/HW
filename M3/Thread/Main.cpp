#include <iostream>
#include <thread>
#include "InfInt.h"




InfInt RisingFactorial(const size_t & start, const size_t & end) {

	if (start == end)
		return 1;

	InfInt result(start + 1);
	for (size_t i = start + 2; i <= end; ++i)
		result *= i;

	return result;
}


InfInt Factorial(const size_t & number) {

	InfInt result(1);
	for (size_t i = 2; i <= number; ++i)
		result *= i;

	return result;

}

void SetFactorial(const size_t & number, InfInt * set) {
	*set = Factorial(number);
}

void SetRisingFactorial(const size_t & start, const size_t & end, InfInt * set) {
	*set = RisingFactorial(start, end);
}

InfInt Sample(const size_t & n, const size_t k) {

	if (n < k)
		return 0;

	InfInt a(1);
	InfInt b(1);
	
	size_t max(k);
	size_t min(n - k);
	if (n - k > k)
		std::swap(max, min);

	std::thread thr1(&SetFactorial, min, &a);
	std::thread thr2(&SetRisingFactorial, max, n, &b);

	thr1.join();
	thr2.join();

	InfInt result = b / a;

	return result;

}


int main() {

	std::cout << Sample(3, 1) << std::endl;

	system("pause");

}
