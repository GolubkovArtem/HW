#include "TString.h"

TString::~TString()
{
	delete[] Data;
}

TString::TString()
{
	Data = new char;
	*Data = '\0';
}

TString::TString(const TString& rhs)
{
	int i(-1);
	char* buf = new char[128];
	do
	{
		i++;
		buf[i] = rhs[i];
	} while (rhs[i] != '\0');
	Data = new char[i + 1];
	for (; i >= 0; i--) (*this)[i] = buf[i];
	delete[] buf;
}

TString::TString(const char * data)
{
	int i(-1);
	char* buf = new char[128];
	do
	{
		i++;
		buf[i] = data[i];
	} while (data[i] != '\0');
	Data = new char[i + 1];
	for (; i >= 0; i--) (*this)[i] = buf[i];
	delete[] buf;
}

TString& TString:: operator = (const TString& rhs)
{
	if ((*this) == rhs) return (*this);
	int i(0);
	delete[] Data;
	Data = new char[rhs.Size() + 1];
	while (rhs[i] != '\0')
	{
		(*this)[i] = rhs[i];
		i++;
	}
	(*this)[i] = '\0';
	return *this;
}

TString& TString:: operator += (const TString& rhs)
{
	char* buf = new char [(*this).Size() + rhs.Size() + 1];
	int i(0);
	while ((*this)[i] != '\0')
	{
		buf[i] = (*this)[i];
		i++;
	}
	int j(0);
	while (rhs[j] != '\0')
	{
		buf[i] = rhs[j];
		i++;
		j++;
	}
	buf[i] = '\0'; 
	*this = buf;
	delete[] buf;
	return *this;
}

bool TString:: operator ==(const TString& rhs) const
{
	int i(0);
	while ((*this)[i] == rhs[i])
	{
		if (rhs[i] == '\0') return 1;
		i++;
	}
	return 0;
}

bool TString:: operator <(const TString& rhs) const
{
	int i(0);
	while ((*this)[i] == rhs[i])
	{
		if (rhs[i] == '\0') return 0;
		i++;
	}
	if ((*this)[i] > rhs[i]) return 0;
	return 1;
}

size_t TString::Find(const TString& substr) const
{
	int i(0);
	if (substr[0] == '\0') return -1;
	while ((*this)[i] != '\0')
	{
		int j(0);
		int i1(i);
		while (substr[j] != '\0' && (*this)[i1] == substr[j])
		{
			i1++;
			j++;
		}
		if (substr[j] == '\0') return (i1 - substr.Size());
		i++;
	}
	return -1;
}

void TString::Replace(char oldSymbol, char newSymbol)
{
	int i(0);
	while ((*this)[i] != '\0')
	{
		if ((*this)[i] == oldSymbol) (*this)[i] = newSymbol;
		i++;
	}
}

size_t TString::Size() const
{
	int i(0);
	while ((*this)[i] != '\0') i++;
	return i;
}

bool TString::Empty() const
{
	if ((*this)[0] == '\0') return 1;
	return 0;
}

char TString:: operator[](size_t index) const
{
	return Data[index];
}

char& TString:: operator[](size_t index)
{
	char* buf = Data;
	for (int i(0); i < index; i++) buf++;
	char& buf1 = *buf;
	return buf1;
}

void TString::RTrim(char symbol)
{
	int i = (*this).Size() - 1;
	while (i >= 0 && (*this)[i] == symbol) i--;
	char* buf = new char[i + 2];
	buf[i + 1] = '\0';
	for (; i >= 0; i--) buf[i] = (*this)[i];
	(*this) = buf;
	delete[] buf;
}

void TString::LTrim(char symbol)
{
	int i(0);
	while ((*this)[i] == symbol) i++;
	char* buf = new char[(*this).Size() + 1 - i];
	int j;
	for (j = 0; j < (*this).Size() + 1 - i; j++) buf[j] = (*this)[i + j];
	(*this) = buf;
	delete[] buf;
}

TString operator + (const TString & a, const TString & b)
{
	TString buf;
	buf += a;
	buf += b;
	return buf;
}

bool operator != (const TString & a, const TString & b)
{
	if (a == b) return 0;
	return 1;
}

bool operator > (const TString & a, const TString & b)
{
	return (b < a);
}

std::ostream & operator<<(std::ostream &out, const TString &str)
{
	std::cout << str.Data << std::endl;
	return out;
}
