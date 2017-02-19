#include <iostream>
#include "TVector.h"

TVector::~TVector()
{
	delete[] PVector;
}

TVector::TVector()
{
	PVector = new double[1];
	PVector[0] = 0;
	Length = 0;
}

TVector::TVector(const TVector& rhs)
{
	PVector = new double[rhs.VectorLength() + 1];
	memcpy(PVector, rhs.PVector, (rhs.VectorLength() + 1) * sizeof(double));
	Length = rhs.VectorLength();
}

TVector::TVector(const double* vector, int length)
{
	PVector = new double[length];
	memcpy(PVector, vector, length * sizeof(double));
	Length = length;
}

TVector& TVector::operator = (const TVector& vector)
{
	delete[] PVector;
	PVector = new double[vector.VectorLength()];
	memcpy(PVector, vector.PVector, (vector.VectorLength() + 1) * sizeof(double));
	Length = vector.VectorLength();
	return (*this);
}

double TVector::operator [] (int index) const
{
	return PVector[index];
}

int TVector::VectorLength() const
{
	return Length;
}

TVector operator + (const double* vector1, const TVector vector2)
{
	if (vector1[0] != vector2.VectorLength())
	{
		TVector buf0;
		return buf0;
	}
	double* mas = new double[vector2.VectorLength()];
	for (int i = 0; i < vector2.VectorLength(); i++) mas[i] = vector1[i + 1] + vector2[i];
	TVector buf(mas, vector2.VectorLength());
	delete[] mas;
	return buf;
}

std::ostream& operator << (std::ostream& out, const TVector& vector)
{
	int i(0);
	for (i = 0; i < vector.VectorLength(); i++) out << vector[i];
	return out;
}
