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

std::ostream& operator << (std::ostream& out, const TOrb& orb)
{
	out << "Radius is " << orb.Radius
		<< " Surface is " << orb.Surface()
		<< "\n";
	return out;
}
