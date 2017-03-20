#include <iostream>
#include <algorithm>

class TInteger
{
	int Integer;
public:
	TInteger() :Integer()
	{}
	TInteger(const int & integer) {
		Integer = integer;
	}
	TInteger(const TInteger & integer) {
		Integer = integer.Integer;
	}


	int operator - () const {
		return -Integer;
	}
	int operator + () const {
		return Integer;
	}
	int operator ++ () {
		if (Integer + 1 < Integer)
			throw("OverFlow");
		return ++Integer;
	}
	int operator ++ (int) {
		if (Integer + 1 < Integer)
			throw("OverFlow");
		return Integer++;
	}
	int operator -- () {
		if (Integer - 1 > Integer)
			throw("OverFlow");
		return --Integer;
	}
	int operator -- (int) {
		if (Integer - 1 > Integer)
			throw("OverFlow");
		return Integer--;
	}


	int operator + (const TInteger & integer) const {
		this->TryAdd(integer);
		return Integer + integer.Integer;
	}
	int operator - (const TInteger & integer) const {
		this->TryAdd(-integer);
		return Integer - integer.Integer;
	}
	int operator * (const TInteger & integer) const {
		this->TryMyltiply(integer);
		return Integer * integer.Integer;
	}
	int operator / (const TInteger & integer) const {
		this->TryDivide(integer);
		return Integer / integer.Integer;
	}
	int operator % (const TInteger & integer) const {
		this->TryDivide(integer);
		return Integer % integer.Integer;
	}
	int operator & (const TInteger & integer) const {
		return Integer & integer.Integer;
	}
	int operator ^ (const TInteger & integer) const {
		return Integer ^ integer.Integer;
	}
	int operator | (const TInteger & integer) const {
		return Integer | integer.Integer;
	}
	int operator << (const TInteger & integer) const {
		return Integer << integer.Integer;
	}
	int operator >> (const TInteger & integer) const {
		return Integer >> integer.Integer;
	}


	TInteger & operator = (const TInteger & integer) {
		Integer = integer.Integer;
		return *this;
	}
	TInteger & operator += (const TInteger & integer) {
		this->TryAdd(integer.Integer);
		Integer += integer.Integer;
		return *this;
	}
	TInteger & operator -= (const TInteger & integer) {
		this->TryAdd(-integer.Integer);
		Integer -= integer.Integer;
		return *this;
	}
	TInteger & operator *= (const TInteger & integer) {
		this->TryMyltiply(integer.Integer);
		Integer *= integer.Integer;
		return *this;
	}
	TInteger & operator /= (const TInteger & integer) {
		this->TryDivide(integer);
		Integer /= integer.Integer;
		return *this;
	}
	TInteger & operator %= (const TInteger & integer) {
		this->TryDivide(integer);
		Integer %= integer.Integer;
		return *this;
	}
	TInteger & operator <<= (const TInteger & integer) {
		Integer <<= integer.Integer;
		return *this;
	}
	TInteger & operator >>= (const TInteger & integer) {
		Integer >>= integer.Integer;
		return *this;
	}
	TInteger & operator &= (const  TInteger & integer) {
		Integer &= integer.Integer;
		return *this;
	}
	TInteger & operator ^= (const TInteger & integer) {
		Integer ^= integer.Integer;
		return *this;
	}


	bool operator == (const TInteger & integer) const {
		return Integer == integer.Integer;
	}
	bool operator != (const TInteger & integer) const {
		return Integer != integer.Integer;
	}
	bool operator < (const TInteger & integer) const {
		return Integer < integer.Integer;
	}
	bool operator > (const TInteger & integer) const {
		return Integer > integer.Integer;
	}
	bool operator >= (const TInteger & integer) const {
		return Integer >= integer.Integer;
	}
	bool operator <= (const TInteger & integer) const {
		return Integer <= integer.Integer;
	}


	void TryAdd(const TInteger & integer) const {
		int buf = integer.Integer + Integer;
		int sign1 = (Integer > 0) - (Integer < 0);
		int sign2 = (integer > 0) - (integer < 0);
		if (sign1 * sign2 > 0 && integer.Integer * sign1 > sign1 * buf)
			throw("OverFlow");
	}
	void TryMyltiply(const TInteger & integer) const {
		TInteger buf = integer.Integer * Integer;
		if (buf != 0 && buf / integer != Integer)
			throw("OverFlow");
	}
	void TryDivide(const TInteger & integer) const {
		if (Integer == -pow(2, 31) && integer.Integer == -1)
			throw ("OverFlow");
	}


	friend std::ostream & operator << (std::ostream & , const TInteger & );
};

std::ostream & operator << (std::ostream & out, const TInteger & integer) {
	out << integer.Integer;
	return out;
}
