#include "meetingWindow.h"

MeetingWindow::MeetingWindow(int x, int y, int w, int h, const std::string& title) : TDT4102::AnimationWindow{x, y, w, h, title}, 
quitBtn{{w - pad*2, pad}, btnW, btnH, "Quit "},  personName{{3*pad, pad}, fieldW, fieldH, ""},
personEmail{{3*pad, pad+fieldH}, fieldW, fieldH, ""}, personSeats{{3*pad, pad+2*fieldH}, fieldW, fieldH, ""},
addPersonBtn{{3*pad, pad + 3*fieldH},2*btnW, btnH, "Add person"}
{
    add(quitBtn);
    quitBtn.setCallback(std::bind(&MeetingWindow::cb_quit, this));

    add(personName);
    add(personEmail);
    add(personSeats);
    add(addPersonBtn);
    addPersonBtn.setCallback(std::bind(&MeetingWindow::cb_new_person, this));


    draw_text({pad,pad}, "Name: ");
    
    draw_text({pad,pad + fieldH}, "Email: ");
    
    draw_text({pad,pad + 2*fieldH}, "Seats: ");
}

void MeetingWindow::newPerson(){
    std::string name = personName.getText();
    std::string email = personEmail.getText();
    std::string seats = personSeats.getText();
    try{
        int seatsInt = std::stoi(seats);
            if (name.size() && email.size() && seatsInt >= 0){
            person.emplace_back(new Person{name, email,std::make_unique<Car>(seatsInt-1)});
            }
    } catch (const std::invalid_argument& e){
        std::cout << "Invalid input for seats" << std::endl;
    }
    personName.setText("");
    personEmail.setText("");
    personSeats.setText("");
}


void MeetingWindow::cb_quit(){
    close();
}

void MeetingWindow::cb_new_person(){
    newPerson();
}

std::ostream& operator<< (std::ostream& os, const MeetingWindow& w)
{
    os << w.person.size() << " added people: " << std::endl;;
    for (const auto& p : w.person)
    {
        os << p->getName() << std::endl;
    }
    return os;
}