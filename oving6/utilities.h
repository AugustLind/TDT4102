#pragma once
#include "std_lib_facilities.h"

void writeToFile();

void writeToFileNumbers();

class CourseCatalog{
      map<string, string> Courses;
public:
    void addCourse(string newCode, string newName);
    void removeCourse(string code);
    string getCourse(string code);
    friend ostream& operator<<(ostream& os, const CourseCatalog& c);
    void testCourseCatalog();
    void saveCatalog();
    void loadCatalog();
};

