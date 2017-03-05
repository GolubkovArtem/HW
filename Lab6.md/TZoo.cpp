#include "TZoo.h"

TZoo::~TZoo()
{
	for (size_t i = 0; i < NumAnimals; ++i) delete Animals[i];
	delete[] Animals;
}

TZoo::TZoo(size_t capacity)
	: Capacity(capacity)
	, NumAnimals(0)
	, Time(0)
{
	Animals = new TPtrAnimal[Capacity];
	memset(Animals, 0, sizeof(TPtrAnimal) * Capacity);
}

size_t TZoo::GetCapacity() const
{
	return Capacity;
}

TAnimal** TZoo::operator () (size_t index)
{
	return &Animals[index];
}

bool TZoo::AddNewAnimal(TAnimal ** newAnimal)
{
	if (newAnimal == nullptr || NumAnimals == Capacity) return false;
	for (size_t i = 0; i < Capacity - 1; ++i)
	{
		if (Animals[i] == nullptr)
		{
			Animals[i] = *newAnimal;
			break;
		}
	}
	*newAnimal = nullptr;
	++NumAnimals;
	return true;
}

bool TZoo::DeleteAnimal(TAnimal ** animal)
{
	if (animal == nullptr) return false;
	for (size_t i = 0; i < Capacity - 1; ++i)
	{
		if (Animals[i] == *animal)
		{
			Animals[i] = nullptr;
			break;
		}
	}
	--NumAnimals;
	return true;
}

bool TZoo::GiveAnimalToZoo(TZoo & zoo, TAnimal ** animal1, TAnimal ** animal2)
{
	if ((**animal1).GetOrder() != (**animal2).GetOrder()) return 0;
	(*this).DeleteAnimal(animal1);
	zoo.DeleteAnimal(animal2);
	(*this).AddNewAnimal(animal2);
	zoo.AddNewAnimal(animal1);
	return 1;
}


void TZoo::Work()
{
	if (Time <= 12) std::cout << "   " << Time << "  a.m" << std::endl;
	else std::cout << "   " << Time << "  p.m" << std::endl;
	for (size_t i = 0; i < Capacity - 1; ++i)
	{
		if (Animals[i] != nullptr)
		{
			Animals[i]->Live(Time);
			if (Time == 24.f)
				Animals[i]->BirthDay();
		}
	}
	Time += STEP;
	if (Time > 24.f) Time -= 24.f;
}
