#include "std_lib_facilities.h"
#include "utilities.h"

Animal::Animal(string navn, int alder): name{navn}, age{alder} {}

Dog::Dog(string navn, int alder): Animal(navn,alder) {}

Cat::Cat(string navn, int alder): Animal(navn,alder) {}

void testAnimal(){
    vector<unique_ptr<Animal>> animals;
    /*
    animals.emplace_back(new Animal{"Rev",4});
    animals.emplace_back(new Animal{"Koala",420});
    */
    animals.emplace_back(new Cat{"Evert",102});
    animals.emplace_back(new Dog{"Hans",12});

    for (const auto& animal : animals) {
        cout << animal->toString() << endl;
    }
}