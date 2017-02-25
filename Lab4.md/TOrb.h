#include <iostream>
#include "TCircle.h"

class TOrb: public TCircle
{
public:
	TOrb();
	TOrb(size_t radius);
	double Surface() const;
	void Show() const;
};
