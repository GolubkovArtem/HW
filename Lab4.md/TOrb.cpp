#include <iostream>
#include "TOrb.h"


TOrb::TOrb()
{
	Radius = 0;
}

TOrb::TOrb(size_t radius)
{
	Radius = radius;
}

double TOrb::Surface() const
{
	return (4. / 3 * M_PI * pow(Radius, 3));
}

void TOrb::Show() const
{
	std::cout << "Radius is " << Radius
		  << " Surface is " << this->Surface()
  		  << "\n";
}
