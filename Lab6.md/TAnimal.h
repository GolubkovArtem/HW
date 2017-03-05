#include <string>
#include <iostream>

class TAnimal
{
protected:
	std::string Name;
	size_t Age;
	bool Male;
public:
	virtual ~TAnimal() = default;
	TAnimal()
		: Name()
		, Age()
		, Male(rand() % 2)
	{ }
	TAnimal(const std::string & name)
	: Name(name)
		, Age(0)
		, Male(rand() % 2)
	{ }
	TAnimal(const std::string & name, bool male)
		: Name(name)
		, Age(0)
		, Male(male)
	{ }
	virtual void Live(float time) const = 0;
	virtual bool Reproduction(const TAnimal & animal) const = 0;
	virtual bool Death() const = 0;
	virtual std::string GetOrder() const = 0;
	virtual std::string GetSpecies() const = 0;
	std::string GetName() const
	{
		return Name;
	}
	size_t GetAge() const
	{
		return Age;
	}
	bool GetMale() const
	{
		return Male;
	}
	void BirthDay()
	{
		Age++;
	}
};
