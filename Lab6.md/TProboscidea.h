#include "TArtiodactyla.h"

class TProboscidea :public TAnimal
{
protected:
	static std::string Order;
public:
	virtual ~TProboscidea() = default;
	TProboscidea(const std::string & name) :TAnimal(name)
	{}
	TProboscidea(const std::string & name, bool male) :TAnimal(name, male)
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



class TElephas :public TProboscidea
{
private:
	static std::string Species;
public:
	virtual ~TElephas() = default;
	TElephas(const std::string & name) :TProboscidea(name)
	{}
	TElephas(const std::string & name, bool male) :TProboscidea(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 12.f && time < 14.f || time >= 22.f && time < 0.f)
			std::cout << "elephant " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 14.f && time < 16.f)
			std::cout << "elephant " << TAnimal::GetName() << " is sleeping" << std::endl;
		else if (time >= 6.f && time < 12.f)
			std::cout << "elephant " << TAnimal::GetName() << " is swiming" << std::endl;
		else
			std::cout << "elephant " << TAnimal::GetName() << " is walking" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 5 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 7 && rand() % Age <= Age - 5 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Proboscidea");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};



class TLoxodonta :public TProboscidea
{
private:
	static std::string Species;
public:
	virtual ~TLoxodonta() = default;
	TLoxodonta(const std::string & name) :TProboscidea(name)
	{}
	TLoxodonta(const std::string & name, bool male) :TProboscidea(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 8.f && time < 14.f || time >= 18.f && time < 4.f)
			std::cout << "savann elephant " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 14.f && time < 16.f)
			std::cout << "savann elephant " << TAnimal::GetName() << " is sleeping" << std::endl;
		else
			std::cout << "savann elephant " << TAnimal::GetName() << " is walking" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 5 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 7 && rand() % Age <= Age - 5 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Proboscidea");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};
