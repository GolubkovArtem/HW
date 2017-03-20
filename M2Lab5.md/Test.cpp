#include "TNotCopyable.h"
#include <iostream>

int main()
{
	try
	{
		TNotCopyable obj;

		obj.OpenToWrite("rit1.txt");

		obj.OpenToRead("rit1.txt");

		obj.Close();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	system("pause");
}
