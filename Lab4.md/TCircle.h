#include <iostream>
#define M_PI 3.1415926535

class TCircle
{
protected:
	size_t Radius;
public:
	TCircle();
	TCircle(size_t radius);
	virtual double Surface() const;
	virtual void Show() const;
};
