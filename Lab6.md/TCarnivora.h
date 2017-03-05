#include "TProboscidea.h"

class TCarnivora :public TAnimal
{
protected:
	static std::string Order;
public:
	virtual ~TCarnivora() = default;
	TCarnivora(const std::string & name) :TAnimal(name)
	{}
	TCarnivora(const std::string & name, bool male) :TAnimal(name, male)
	{}
	void Live(float time) const = 0;
	bool Reproduction(const TAnimal & animal) const = 0;
	bool Death() const = 0;
	virtual std::string GetOrder() const override
	{
		return Order;
	}
	std::string GetSpecies() const = 0;
};



class TLeo :public TCarnivora
{
private:
	static std::string Species;
public:
	virtual ~TLeo() = default;
	TLeo(const std::string & name) :TCarnivora(name)
	{}
	TLeo(const std::string & name, bool male) :TCarnivora(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 6.f && time < 8.f)
			std::cout << "leon " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 22.f && time < 6.f || time >= 10.f && time < 14.f)
			std::cout << "leon " << TAnimal::GetName() << " is sleeping" << std::endl;
		else
			std::cout << "leon " << TAnimal::GetName() << " is walking" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 2 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 5 && rand() % Age <= Age - 4 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Carnivora");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};



class TTigris :public TCarnivora
{
private:
	static std::string Species;
public:
	virtual ~TTigris() = default;
	TTigris(const std::string & name) :TCarnivora(name)
	{}
	TTigris(const std::string & name, bool male) :TCarnivora(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 6.f && time < 8.f)
			std::cout << "tiger " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 22.f && time < 4.f || time >= 10.f && time < 12.f)
			std::cout << "tiger " << TAnimal::GetName() << " is sleeping" << std::endl;
		else
			std::cout << "tiger " << TAnimal::GetName() << " is patroling" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 3 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 5 && rand() % Age <= Age - 4 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Carnivora");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};
