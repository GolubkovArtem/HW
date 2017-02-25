#include <iostream>
#include "TCircle.h"

class TOrb: public TCircle
{
public:
	TOrb();
	TOrb(size_t radius);
	double Surface() const;
	friend std::ostream& operator << (std::ostream&, const TOrb&);
};

std::ostream& operator << (std::ostream& out, const TOrb& orb);
