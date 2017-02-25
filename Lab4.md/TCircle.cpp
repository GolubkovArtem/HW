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

std::ostream& operator << (std::ostream& out, const TCircle& circle)
{
	out << "Radius is " << circle.Radius 
		<< " Surface is " << circle.Surface()
		<< "\n";
	return out;
}
