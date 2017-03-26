#include <iostream>

void MetaPrint(int a)
{
	static int i = 0;
	if (a >= i)
	{
		std::cout << i++ << std::endl;
		MetaPrint(a);
	}
	i = 0;
}

int main()
{
	MetaPrint(100);
	system("pause");
}
