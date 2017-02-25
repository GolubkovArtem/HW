#include <iostream>

class TVector
{
private:
	double* PVector;
	int Length;
public:
	~TVector();
	TVector();
	TVector(const TVector& rhs);
	TVector(const double* vector, int length);
	double operator [] (int index) const;
	TVector& operator = (const TVector& vector);
	friend std::ostream& operator << (std::ostream&, const TVector&);
	friend TVector operator + (const double* , const TVector& );
};
TVector operator + (const double* vector1, const TVector& vector2);


std::ostream& operator << (std::ostream& out, const TVector& vector);
