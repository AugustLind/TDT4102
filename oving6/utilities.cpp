#include "std_lib_facilities.h"
#include "utilities.h"

void writeToFile(){
    string inputWord;
    bool cont = true;
    filesystem::path fileName{"file.txt"};
    ofstream outputStream{fileName};
    cout << "Skriv inn noe til textfilen eller skriv quit for aa avlutte ";
    while (cont){
        cout << "\n" << "Input: ";
        cin >> inputWord;
        if (inputWord == "quit"){
            cont = false;
        }else{
            outputStream << inputWord << endl;
        }
    }
}

void writeToFileNumbers(){
    ifstream inputStream{"file.txt"};
    if (!inputStream) {
        cout << "Kunne ikke åpne filen" << endl;
    } else{
    filesystem::path fileName{"fileNumbers.txt"};
    ofstream outputStream{fileName};
    string line;
    int round{1};
    while(getline(inputStream,line)){
        outputStream << round << " " << line << endl;
        round += 1;
    }
    }
}

const map<string, string> Catalog{
};

void CourseCatalog::addCourse(string newCode, string newName){
    Courses.insert({newCode,newName});
}

void CourseCatalog::removeCourse(string code){
    Courses.erase(code);
}

string CourseCatalog::getCourse(string code){
    string name = Courses.at(code);
    return name;
}

ostream& operator<<(ostream& os, const CourseCatalog& c) {
    for (const auto& [code, name] : c.Courses) {
        os << code << ": " << name << endl;
    }
    return os;
}

void CourseCatalog::testCourseCatalog() {
    addCourse("TDT4110", "Informasjonsteknologi grunnkurs");
    addCourse("TDT4102", "Prosedyre- og objektorientert programmering");
    addCourse("TMA4100", "Matematikk 1");
    addCourse("TDT4102", "C++");
    Courses["TDT4102"] = "C++";

    cout << "Kurs i katalogen" << endl;
    cout << *this;
}

void CourseCatalog::saveCatalog(){
    filesystem::path fileName{"catalog.txt"};
    ofstream outputStream{fileName};
    map c = Catalog;
    for (const auto& [code, name] : Courses) {
        outputStream << code << ';' << name << '\n';
    }
}


void CourseCatalog::loadCatalog(){
    ifstream inputStream{"catalog.txt"};
    if (!inputStream) {
        cout << "Kunne ikke åpne filen" << endl;
    } else{
    string line;
    while(getline(inputStream,line)){
        stringstream ss(line);
        string code;
        string name;
        getline(ss, code, ';');
        getline(ss, name, ';');
        addCourse(code, name);
    }
    }
}