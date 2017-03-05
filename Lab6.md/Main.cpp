#include <thread>
#include "TZoo.h"

std::string TArtiodactyla::Order("Artiodactyla");
std::string TGiraffa::Species("Giraffa");
std::string THippopotamus::Species("Hippopotamus");
std::string TProboscidea::Order("Proboscidea");
std::string TElephas::Species("Elephas");
std::string TLoxodonta::Species("Loxodonta");
std::string TCarnivora::Order("Carnivora");
std::string TLeo::Species("Leo");
std::string TTigris::Species("Tigris");


int main()
{
	TZoo myZoo(24);
	TAnimal * Edi = new TGiraffa("Edi", 1);
	TAnimal * Christa = new TGiraffa("Christa", 0);
	TAnimal * LinVan = new TElephas("LinVan", 1);
	TAnimal * Mary = new TElephas("Mary", 0);
	TAnimal * Zeus = new TLeo("Zeus", 1);
	TAnimal * Levkofrina = new TLeo("Levkofrina", 0);

	TZoo zooOfBerlin(24);
	TAnimal * Phelps = new THippopotamus("Phelps", 1);
	TAnimal * Gloria = new THippopotamus("Gloria", 0);
	TAnimal * Jumbo = new TLoxodonta("Jumbo", 1);
	TAnimal * Akoko = new TLoxodonta("Akoko", 0);
	TAnimal * ShereKhan = new TTigris("ShereKhan", 1);
	TAnimal * Philipa = new TTigris("Philipa", 0);

	if (!myZoo.AddNewAnimal(&Edi))
		delete Edi;
	if (!myZoo.AddNewAnimal(&Christa))
		delete Christa;
	if (!myZoo.AddNewAnimal(&LinVan))
		delete LinVan;
	if (!myZoo.AddNewAnimal(&Mary))
		delete Mary;
	if (!myZoo.AddNewAnimal(&Zeus))
		delete Zeus;
	if (!myZoo.AddNewAnimal(&Levkofrina))
		delete Levkofrina;

	if (!zooOfBerlin.AddNewAnimal(&Phelps))
		delete Phelps;
	if (!zooOfBerlin.AddNewAnimal(&Gloria))
		delete Gloria;
	if (!zooOfBerlin.AddNewAnimal(&Jumbo))
		delete Jumbo;
	if (!zooOfBerlin.AddNewAnimal(&Akoko))
		delete Akoko;
	if (!zooOfBerlin.AddNewAnimal(&ShereKhan))
		delete ShereKhan;
	if (!zooOfBerlin.AddNewAnimal(&Philipa))
		delete Philipa;

	for (size_t k = 0; k < 100; ++k)
	{
		std::cout << "\n " << k << " Turn " << floor((k * STEP) / 24) << " Year\n";
		myZoo.Work();
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		int buf = STEP;
		for (size_t i = 0; i < myZoo.GetCapacity(); ++i)
		{
			if (k * buf % 24) break;
			if ((*myZoo(i)) != nullptr && (**myZoo(i)).Death())
			{
				std::cout << "\n" << (**myZoo(i)).GetName() << " is dead\n";
				myZoo.DeleteAnimal(myZoo(i));
				delete (*myZoo(i));
			}
		}
		for (size_t i = 0; i < myZoo.GetCapacity(); ++i)
		{
			if (k * buf % 24) break;
			for (size_t j = 0; j < myZoo.GetCapacity(); ++j)
			{
				if ((*myZoo(i)) != nullptr && (*myZoo(j)) != nullptr && (**myZoo(i)).Reproduction(**myZoo(j)) == 1)
				{
					TGiraffa bufAnimal("buf");
					size_t buf1;
					if (bufAnimal.GetMale() == (**myZoo(i)).GetMale()) buf1 = i;
					else buf1 = j;
					TAnimal * NewAnimal = &bufAnimal;
					if ((**myZoo(i)).GetSpecies() == "Giraffa")
					{
					NewAnimal = new TGiraffa((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					else if ((**myZoo(i)).GetSpecies() == "Hippopotamus")
					{
					NewAnimal = new THippopotamus((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					else if ((**myZoo(i)).GetSpecies() == "Elephas")
					{
					NewAnimal = new TElephas((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					else if ((**myZoo(i)).GetSpecies() == "Loxodonta")
					{
					NewAnimal = new TLoxodonta((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					else if ((**myZoo(i)).GetSpecies() == "Leo")
					{
					NewAnimal = new TLeo((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					else if ((**myZoo(i)).GetSpecies() == "Tigris")
					{
					NewAnimal = new TTigris((**myZoo(buf1)).GetName() + 'I', (*NewAnimal).GetMale());
					}
					
					std::cout << "\n" << (*NewAnimal).GetName() << " was born by " << (**myZoo(i)).GetName() << " and " << (**myZoo(j)).GetName() << "\n";
					if (!myZoo.AddNewAnimal(&NewAnimal)) 
						delete NewAnimal;
				}
			}
		}
	}
	system("pause");
}
