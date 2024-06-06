#pragma once 
#include "widgets/TextInput.h"
#include "widgets/Button.h"
#include <string>
#include "AnimationWindow.h" 
#include "meeting.h"   

class MeetingWindow : public TDT4102::AnimationWindow{
    static constexpr int pad{40};
    static constexpr int btnW{100};
    static constexpr int btnH{60};
    static constexpr int fieldW{240};
    static constexpr int fieldH{60};
    TDT4102::Button quitBtn;
    TDT4102::TextInput personName;
    TDT4102::TextInput personEmail;
    TDT4102::TextInput personSeats;
    TDT4102::Button addPersonBtn;
    std::vector<std::shared_ptr<Person>> person;

public: 
    MeetingWindow(int x, int y, int w, int h, const std::string& title);
    void cb_quit();
    void newPerson();
    void cb_new_person();
    friend std::ostream& operator<< (std::ostream& os, const MeetingWindow& mwin);
};