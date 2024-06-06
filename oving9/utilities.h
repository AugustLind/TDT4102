#pragma once
#include <string>
#include <memory>
#include <iostream>

class Car{
    int freeSeats;
public:
    Car(int freeSeats) : freeSeats{freeSeats} {}
    bool hasFreeSeats() const;
    void reserveFreeSeat();

};

class Person{
    std::string name;
    std::string email;
    std::unique_ptr<Car> car;
public:
    Person(std::string name, std::string email, std::unique_ptr<Car> carPtr = nullptr); 
    std::string getName() const;
    std::string getEmail() const;
    void setEmail(std::string newEmail);
    bool hasAvailableSeats() const;
    friend std::ostream& operator<< (std::ostream& os, const Person& person);
};
