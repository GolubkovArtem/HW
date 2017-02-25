#include <iostream>
#include "TCircle.h"

TCircle::TCircle()
{
	Radius = 0;
}

TCircle::TCircle(size_t radius)
{
	Radius = radius;
}

double TCircle::Surface() const
{
	return (M_PI * pow(Radius, 2));
}

void TCircle::Show() const
{
	std::cout << "Radius is " << Radius
		  << " Surface is " << this->Surface()
  		  << "\n";
}
