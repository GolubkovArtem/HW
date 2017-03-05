#include <iostream>
extern float M_PI(3.1415926535);

class TCircle
{
protected:
	size_t Radius;
public:
	TCircle() :Radius(0)
	{}
	TCircle(size_t radius) :Radius(radius)
	{}
	virtual double Surface() const
	{
		return (M_PI * pow(Radius, 2));
	}
	virtual void Show() const
	{
		std::cout << "Radius is " << Radius
			<< " Surface is " << this->Surface()
			<< std::endl;
	}
};
