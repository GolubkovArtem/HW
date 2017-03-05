#include "TAnimal.h"

class TArtiodactyla :public TAnimal
{
protected:
	static std::string Order;
public:
	virtual ~TArtiodactyla() = default;
	TArtiodactyla(const std::string & name) :TAnimal(name)
	{}
	TArtiodactyla(const std::string & name, bool male) :TAnimal(name, male)
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



class TGiraffa :public TArtiodactyla
{
private:
	static std::string Species;
public:
	virtual ~TGiraffa() = default;
	TGiraffa(const std::string & name) :TArtiodactyla(name)
	{}
	TGiraffa(const std::string & name, bool male) :TArtiodactyla(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 8.f && time < 10.f || time >= 14.f && time < 16.f)
			std::cout << "giraffe " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 2.f && time < 4.f)
			std::cout << "giraffe " << TAnimal::GetName() << " is sleeping" << std::endl;
		else
			std::cout << "giraffe " << TAnimal::GetName() << " is walking" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 4 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 6 && rand() % Age <= Age - 4 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Artiodactyla");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};



class THippopotamus :public TArtiodactyla
{
private:
	static std::string Species;
public:
	virtual ~THippopotamus() = default;
	THippopotamus(const std::string & name) :TArtiodactyla(name)
	{}
	THippopotamus(const std::string & name, bool male) :TArtiodactyla(name, male)
	{}
	void Live(float time) const
	{
		if (time >= 2.f && time < 6.f)
			std::cout << "hippo " << TAnimal::GetName() << " is eating" << std::endl;
		else if (time >= 6.f && time < 10.f)
			std::cout << "hippo " << TAnimal::GetName() << " is sleeping" << std::endl;
		else
			std::cout << "hippo " << TAnimal::GetName() << " is swiming" << std::endl;
	}
	bool Reproduction(const TAnimal & animal) const
	{
		if (Age >= 6 && animal.GetAge() >= 4 && Male == 0 && Male != animal.GetMale() && Species == animal.GetSpecies() && rand() % 10 >= 5) return 1;
		return 0;
	}
	bool Death() const
	{
		if (Age >= 8 && rand() % Age <= Age - 6 || Age == 20) return 1;
		return 0;
	}
	std::string GetOrder() const
	{
		return ("Artiodactyla");
	}
	std::string GetSpecies() const
	{
		return Species;
	}
};
