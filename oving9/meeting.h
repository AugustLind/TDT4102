#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "utilities.h"

enum class Campus{Trondheim, Aalesund, Gjovik};

class Meeting{
    int day;
    int startTime;
    int endTime;
    Campus location;
    std::string subject;
    const std::shared_ptr<Person> leader;
    std::vector<std::shared_ptr<Person>> participants;
public:
    Meeting(int day, int startTime, int endTime, std::string subject, Campus location, const std::shared_ptr<Person> leader);
    void addParticipant(std::shared_ptr<Person> person);
    std::vector<std::string> getParticipantList();
    int getStartTime() const;
    int getEndTime() const;
    std::string getCampus() const;
    std::string getSubject() const;
    std::vector<std::shared_ptr<Person>> findPotenialCoDriving(const Meeting& otherMeeting) const;
};

std::ostream& operator<< (std::ostream& os, Meeting meeting);