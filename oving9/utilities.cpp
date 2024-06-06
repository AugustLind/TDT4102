#include "utilities.h"

bool Car::hasFreeSeats() const{
    if (freeSeats == 0){
        return false;
    }
    return true;
}

void Car::reserveFreeSeat(){
    freeSeats -= 1;
}

Person::Person(std::string name, std::string email, std::unique_ptr<Car> carPtr) : name{name}, email{email} {
        std::swap(car,carPtr);
}

std::string Person::getName() const{
    return name;
}

std::string Person::getEmail() const{
    return email;
}

void Person::setEmail(std::string newEmail){
    email = newEmail;
}

bool Person::hasAvailableSeats() const{
    if (car.get() != nullptr){
        return true;
    }
    return false;
}

std::ostream& operator<< (std::ostream& os, const Person& person){
    os << "Navn: " << person.getName() << std::endl;
    os << "Email: " << person.getEmail() << std::endl;
    os << "Har ledig seter " << std::boolalpha << person.hasAvailableSeats() << std::endl;
    return os;
}