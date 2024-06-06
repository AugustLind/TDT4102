#include "meeting.h"

Meeting::Meeting(int day, int startTime, int endTime, std::string subject, Campus location, const std::shared_ptr<Person> leader): 
day{day}, startTime{startTime}, endTime{endTime}, subject{subject},location{location}, leader{leader} 
{
    participants.push_back(leader);
}

void Meeting::addParticipant(std::shared_ptr<Person> person) {
    participants.push_back(person);
}

std::vector<std::string> Meeting::getParticipantList(){
    std::vector<std::string> vecParticipants;
    for(int i{0}; i < participants.size(); i++){
        vecParticipants.push_back(participants.at(i)->getName());
    }
    return vecParticipants;
}

int Meeting::getStartTime() const{
    return startTime;
}

int Meeting::getEndTime() const{
    return endTime;
}
    
std::string Meeting::getCampus() const{
    switch (location) {
    case Campus::Trondheim:
        return "Trondheim";
    case Campus::Aalesund:
        return "Aalesund";
    case Campus::Gjovik:
        return "Gjovik";
}
}
    
std::string Meeting::getSubject() const{
    return subject;
}

std::ostream& operator<< (std::ostream& os, Meeting meeting){
    os << "Emnet: " << meeting.getSubject() << std::endl;
    os << "Campus: " << meeting.getCampus() << std::endl;
    os << "Fra: " << meeting.getStartTime() << " Til: " << meeting.getEndTime() << std::endl;
    std::vector<std::string> vecP = meeting.getParticipantList();
    os << "Deltakere: " << std::endl;
    for (int i{0}; i < vecP.size(); i++){
        os << vecP.at(i) << std::endl;
    }
    return os;
};

std::vector<std::shared_ptr<Person>> Meeting::findPotenialCoDriving(const Meeting& otherMeeting) const{
    std::vector<std::shared_ptr<Person>> vecCoDriving;
    if (location == otherMeeting.location && std::abs(startTime - otherMeeting.startTime) <= 1 && 
    std::abs(endTime - otherMeeting.endTime) <= 1 && day == otherMeeting.day){
    for (int i{0}; i < otherMeeting.participants.size(); i++){
        if (otherMeeting.participants.at(i)->hasAvailableSeats() == true){
            vecCoDriving.push_back(otherMeeting.participants.at(i));
        }
    }
    }
    return vecCoDriving;
}