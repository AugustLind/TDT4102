#include <iostream>
#include "utilities.h"
#include "meeting.h"
#include "meetingWindow.h"


int main() {
    int value{0};
    std::cout << "1) Tester at ledige seter fungerer" << std::endl;
    std::cout << "2) Tester Person og mailendring" << std::endl;
    std::cout << "3) Tester Moeter" << std::endl;
    std::cout << "4) Tester GUI" << std::endl;
    std::cin >> value;
    switch(value){
        case 1:{
            Car c(1);
            std::cout << c.hasFreeSeats() << std::endl;
            c.reserveFreeSeat();
            std::cout << c.hasFreeSeats() << std::endl;
            break;
        }
        case 2:{
            std::unique_ptr<Person> p1 = std::make_unique<Person>("VVD","goat@gmail.com");
            std::cout << p1->getEmail() << std::endl;
            p1->setEmail("liverpool@gmail.com");
            std::unique_ptr<Person> p2 = std::make_unique<Person>("Jan","hei@gmail.com", std::make_unique<Car>(1));
            std::cout << *p1 << std::endl;
            std::cout << *p2 << std::endl;
            break;
        }
        case 3:{
            std::shared_ptr<Person> p1 = std::make_shared<Person>("VVD", "goat@gmail.com");
            std::shared_ptr<Person> p2 = std::make_shared<Person>("Jan", "hei@gmail.com", std::make_unique<Car>(1));
            Meeting m1{1, 14, 15, "C++", Campus::Trondheim, p1};
            m1.addParticipant(p2);
            std::cout << m1 << std::endl;

            std::shared_ptr<Person> p3 = std::make_shared<Person>("Frode", "frode@gmail.com", std::make_unique<Car>(2));
            Meeting m2{1, 13, 14, "Statistikk", Campus::Trondheim, p3};
            std::vector<std::shared_ptr<Person>> coDriving = m1.findPotenialCoDriving(m2);
            for (int i = 0; i < coDriving.size(); i++)
                std::cout << coDriving.at(i)->getName() << std::endl;
            break;
        }
        case 4:{
            MeetingWindow w{100, 100, 1024, 640, "Moete GUI"};
            w.wait_for_close();
            std::cout << w << std::endl;
            break;
        }
        default:{
            std::cout << "Du har skrevet inn en ugyldig verdi" << std::endl;
            break;
        }
    };

    return 0;
}

