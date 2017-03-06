#include <iostream>

class TPair
{
protected:
	int First;
	int Second;
public:
	TPair();
	TPair(const TPair& pair);
	TPair(int first, int second);
	virtual void operator () (int first, int second);
	TPair& operator = (const TPair& pair);
	TPair operator + (const TPair& pair);
	friend std::ostream& operator << (std::ostream& , const TPair& );
};

std::ostream& operator << (std::ostream& out, const TPair& pair);
