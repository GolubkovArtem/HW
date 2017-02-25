#include <iostream>
#include "TCircle.h"

class TOrb: public TCircle
{
public:
	TOrb();
	TOrb(size_t radius);
	double Surface() const;
	double Size() const;
	void Show() const;
};
