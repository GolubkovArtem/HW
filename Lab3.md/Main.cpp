#include <iostream>
#include "TVector.h"

int main() 
{
	TVector vec1;
	double str1[5] = { 4, 1, 1 ,0, 0 };
	double str2[4] = { 0, 0, 1, 1 };
	TVector vec2(str2, 4);
	vec1 = vec2;
	TVector vec3 = str1 + vec2;
	std::cout << vec1 << std::endl;
	std::cout << vec3 << std::endl;
	system("pause");
}
