#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

bool Search(std::string string, std::string sFile)
{
	std::fstream file(sFile, std::fstream::in);
	std::string bufString;
	while (std::getline(file, bufString) && !bufString.empty())
		if (bufString == string)
			return 1;
	file.close();
	return 0;
}

int main()
{
	const std::string sFile1 = "C:\\Users\\Артём\\Desktop\\rit1.txt";
	const std::string sFile2 = "C:\\Users\\Артём\\Desktop\\rit2.txt";
	std::string bufString;
	std::fstream file1(sFile1, std::fstream::in);
	while (std::getline(file1, bufString) && !bufString.empty())
		if (!Search(bufString, sFile2))
			std::cout << bufString << std::endl;
	file1.close();
	std::fstream file2(sFile2, std::fstream::in);
	while (std::getline(file2, bufString) && !bufString.empty())
		if (!Search(bufString, sFile1))
			std::cout << bufString << std::endl;
	file2.close();
	system("pause");
}
