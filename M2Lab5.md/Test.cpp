#include "TNotCopyable.h"
#include <iostream>

CloseCheck * CloseCheck::Head(nullptr);

int main()
{
	while (1)
	{
		TNotCopyable obj1;
		try
		{
			TNotCopyable obj2;

			obj1.OpenToWrite("C:\\Users\\Артём\\Desktop\\rit1.txt");

			obj2.OpenToWrite("C:\\Users\\Артём\\Desktop\\rit2.txt");

			obj2.OpenToRead("C:\\Users\\Артём\\Desktop\\rit2.txt");

			obj1.Close();
			obj2.Close();
		}
		catch (const std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	system("pause");
}
