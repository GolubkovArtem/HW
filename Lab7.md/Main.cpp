#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

const size_t n = 2;

bool Palindrome(const std::string & string)
{
	auto iter1 = string.begin(), iter2 = --string.end();
	for (size_t i = 0; i < string.size() / 2; ++i, ++iter1, --iter2)
		if (*iter1 != *iter2) return 0;
	return 1;
}

std::string Search(std::string & string)
{
	std::string bufString1, bufString2;
	std::fstream file("C:\\Users\\Артём\\Desktop\\rit.txt", std::fstream::in);
	while (std::getline(file, bufString1) && !bufString1.empty())
	{
		bufString2 += ' ' + bufString1;
	}
	auto iter = std::search(bufString2.cbegin(), bufString2.cend(), string.cbegin(), string.cend());
	size_t position = std::distance(bufString2.cbegin(), iter);
	if ((iter - bufString2.cbegin() > 1 && isalnum(*(iter - 1)))
		|| (iter - bufString2.cbegin() < bufString2.size() - 1 && isalnum(*(iter + string.size()))))
			position = bufString2.size();
	auto i(string.size());
	if (position != bufString2.size())
	{
		size_t j = n + 1;
		while (j && iter - bufString2.cbegin() > 1)
		{
			++i;
			--iter;
			if (ispunct(*iter) || isspace(*iter))
			{
				--j;
				while (iter - bufString2.cbegin() > 1 
					&& ispunct(*iter) 
					|| isspace(*iter) 
					|| !isprint(*iter))
				{
					++i;
					--iter;
				}
				if (!j) ++iter;
			}
		}
		iter += i - 1;
		j = n + 1;
		while (j && iter - bufString2.cbegin() < bufString2.size() - 1)
		{
			++i;
			++iter;
			if (ispunct(*iter) || isspace(*iter))
			{
				--j;
				while (iter - bufString2.cbegin() < bufString2.size() - 1 
					&& ispunct(*iter) 
					|| isspace(*iter) 
					|| !isprint(*iter))
				{
					++i;
					++iter;
				}
				if (!j) --iter;
			}
		}
		iter -= i - 1;
		std::string result(i, 'n');
		for (size_t j = 0; j < i; ++j, ++iter) result[j] = (*iter);
		return result;
	}
	file.close();
	return "";
}

int main()
{
	std::string string;
	while (getline(std::cin, string) && !string.empty())
	{
		if (Palindrome(string))
			std::cout << string << " is palindrome\n";
		else
			std::cout << string << " isn't palinddrome\n";
	}
	std::cout << "Enter '_' to stop\n";
	while (std::cin >> string && string != ("_"))
	{
		std::cout << Search(string) << std::endl;
	}
	system("pause");
}
