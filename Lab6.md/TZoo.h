#include "TCarnivora.h"

const float STEP = 24;

class TZoo
{
	float Time;
	typedef TAnimal * TPtrAnimal;
	TPtrAnimal * Animals;
	size_t Capacity;
	size_t NumAnimals;
public:
	~TZoo();
	TZoo(size_t capacity);
	size_t GetCapacity() const;
	TAnimal** operator () (size_t index);
	bool AddNewAnimal(TAnimal ** newAnimal);
	bool DeleteAnimal(TAnimal ** animal);
	bool GiveAnimalToZoo(TZoo & zoo, TAnimal ** animal1, TAnimal ** animal2);
	void Work();
};
