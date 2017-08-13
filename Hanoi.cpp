#include <iostream>
#include <vector>
#include <ctime>

const unsigned int tall = 20;


struct Towers {

	std::vector<int> Tower[3];
	float turns;

	Towers()
		: turns(0)
	{
		for (int i = tall; i > 0; --i)
			Tower[0].push_back(i);
	}

	void print() const {
		for (int i = 0; i < 3; ++i) {
			for (auto & j : Tower[i])
				std::cout << j;
			std::cout << std::endl;
		}
	}


	void solve(const int & start = 0, const int & floor = tall, const int & end = 2) {

		if (floor > 1)
			solve(start, floor - 1, 3 - start - end);

		if (floor == 1) {
			Tower[end].push_back(1);
			Tower[start].pop_back();
			++turns;
		}
		else {
			Tower[end].push_back(floor);
			Tower[start].pop_back();
			++turns;
			solve(3 - start - end, floor - 1, end);
		}

	}

};



int main() {

	Towers a;

	a.solve();

	a.print();

	std::cout << a.turns << std::endl;

	system("pause");
}
