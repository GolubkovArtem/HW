#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <class T>
void Swap(T& a, T& b)
{
	T buf = a;
	a = b;
	b = buf;
}

template <class T>
void Swap(T* a, T* b)
{
	T buf = *a;
	*a = *b;
	*b = buf;
}

template <class IT>
void Sort(IT a, IT b)
{
	for (IT i = a; i < b; ++i)
	{
		for (IT j = i; j < b; ++j)
		{
			if (*i > *j) Swap(*i, *j);
		}
	}
}

int main()
{
	std::vector<std::string> vec = {"bb", "aa", "dd"};
	Sort(vec.begin(), vec.end());
	for (int i = 0; i < 3; ++i)
	{
		std::cout << vec[i] << " ";
	}
	int arr[5] = {2, 3, 5, 1, 4};
	Sort(std::begin(arr), std::end(arr));
	for (int i = 0; i < 5; ++i)
	{
		std::cout << arr[i] << " ";
	}
	system("pause");
}
