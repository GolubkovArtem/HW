#include <iostream>
#include "SimplexMethod.h"


using namespace::SimplexMethod;





int main() {

	rational a(1, 2);

	std::vector<rational> table_data
	{
	6, 2, 1,
	-4, -1, -4,
	-5, -2, -a,
	3, 1, 4
	};


	matrix table(4, 3, table_data);
	
	table.print();
	

	std::cout << std::endl;

	
	while (table.step2(table.step1())) {
		table.print();
		std::cout << std::endl;
	}


	while (table.step2(table.step3())) {
		table.print();
		std::cout << std::endl;
	}
	


	system("pause");
}
