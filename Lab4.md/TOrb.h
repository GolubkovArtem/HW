#include "TCircle.h"
extern float M_PI;

class TOrb : public TCircle
{
public:
	TOrb() :TCircle()
	{}
	TOrb(size_t radius) :TCircle(radius)
	{}
	double Surface() const
	{
		return (4. / 3 * M_PI * pow(Radius, 3));
	}

	void Show() const
	{
		std::cout << "Radius is " << Radius
			<< " Surface is " << this->Surface()
			<< std::endl;
	}
};
