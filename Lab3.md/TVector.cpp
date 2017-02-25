#include <iostream>
#include "TVector.h"

TVector::~TVector()
{
	delete[] PVector;
}

TVector::TVector()
{
	PVector = new double[0];
	Length = 0;
}

TVector::TVector(const TVector& rhs)
{
	PVector = new double[rhs.Length];
	memcpy(PVector, rhs.PVector, rhs.Length * sizeof(double));
	Length = rhs.Length;
}

TVector::TVector(const double* vector, int length)
{
	PVector = new double[length];
	memcpy(PVector, vector, length * sizeof(double));
	Length = length;
}

TVector& TVector::operator = (const TVector& vector)
{
	if (PVector == vector.PVector) return (*this);
	delete[] PVector;
	PVector = new double[vector.Length];
	memcpy(PVector, vector.PVector, vector.Length * sizeof(double));
	Length = vector.Length;
	return *this;
}

double TVector::operator [] (int index) const
{
	return PVector[index];
}

TVector operator + (const double* vector1, const TVector& vector2)
{
	TVector buf;
	if (vector1[0] != vector2.Length) return buf;
	delete[] buf.PVector;
	buf.PVector = new double[vector2.Length];
	for (int i = 0; i < vector2.Length; i++) buf.PVector[i] = vector1[i + 1] + vector2[i];
	buf.Length = vector2.Length;
	return buf;
}

std::ostream& operator << (std::ostream& out, const TVector& vector)
{
	for (int i = 0; i < vector.Length; i++) out << vector[i];
	return out;
}
