#include <iostream>
#include "TOrb.h"

int main()
{
	TCircle circle(3);
	circle.Show();
	TOrb orb(3);
	orb.Show();
	TCircle* orb1 = &orb;
	orb1->Show();
	system("pause");
}
