#pragma once
#include "std_lib_facilities.h"

class Animal{
protected:
    string name;
    int age;
public:
    Animal(string navn, int alder);
    virtual ~Animal() {};
    /*
    virtual string toString(){
        return "Animal: " + name + " " + to_string(age);
    }
    */
   virtual string toString() = 0;
};

class Dog : public Animal{
public:
    Dog(string navn, int alder);
    string toString() override{
        return "Dog: " + name + " " + to_string(age);
    }
};

class Cat : public Animal{
public:
    Cat(string navn, int alder);
    string toString() override{
        return "Cat: " + name + " " + to_string(age);
}
};

void testAnimal();