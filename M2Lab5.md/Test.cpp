#include "TNotCopyable.h"
#include <iostream>

int main()
{
	try
	{
		TNotCopyable obj1("rit1.txt", "r");

		TNotCopyable obj2("rit2.txt", "open");

		//TNotCopyable obj3("C:", "open");

		//obj3.Close();

		obj1.Close();

		obj2.Close();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	system("pause");
}
