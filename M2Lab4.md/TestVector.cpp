#include "TVector.h"
#include <iostream>

void printVector(const TVector& vec)
{
	for (int i = 0; i < vec.Size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

int main()
{
	{
		TVector vec;
		for (int i = 0; i < 32; ++i)
			vec.PushBack(i);

		printVector(vec);

		vec.Insert(vec.Begin() + 10, 1000);
		printVector(vec);

		vec.Erase(vec.Begin(), vec.Begin() + 10);
		printVector(vec);

		vec.Erase(vec.Begin());
		printVector(vec);

		std::cout << vec.Front() << std::endl;
		std::cout << vec.Back() << std::endl;

		vec.PopBack();
		std::cout << vec.Back() << std::endl;

		size_t oldSize = vec.Size();
		vec.Resize(44);
		printVector(vec);

		vec.Resize(oldSize);
		printVector(vec);

		TVector vec2;
		for (int i = 0; i < 2; ++i)
			vec2.PushBack(i);


		vec2.Swap(vec);
		printVector(vec2);
		printVector(vec);


		vec = vec2;
		printVector(vec2);
		printVector(vec);

		try
		{
			TVector::value_type item = vec2.At(1000000);
		}
		catch (const std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			vec2.Resize(UINT64_MAX);
		}
		catch (const std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	system("pause");
}
