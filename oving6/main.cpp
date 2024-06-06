#include "std_lib_facilities.h"
#include "utilities.h"
#include "bouncingBall.h"

const map<string, string> capitalsMap {
    {"Norway", "Oslo"},
    {"Sweden", "Stockholm"},
    {"Denmark", "Copenhagen"}
};

string getCapital(const string& country) {
    return capitalsMap.at(country);
}


int main() {
    int choice{0};
    cout << "1) Skrive til txt-fil" << endl;
    cout << "2) Legge til nummer forann hver rad" << endl;
    cout << "3) Debugge hovedsteder" << endl;
    cout << "4) Teste Coursecatalog" << endl;
    cout << "5) Teste og lagre coursecatalog" << endl;
    cout << "6) Laste inn lagret coursecatalog" << endl;
    cout << "7) Bouncingball" << endl;
    cin >> choice;
    switch (choice) {
        case 1: {
            writeToFile();
            break;
        }
        case 2: {
            writeToFileNumbers();
            break;
        }
        case 3:{
            cout << "Capitals:" << endl;
            for (pair<const string, const string> elem : capitalsMap) {
                cout << getCapital(elem.first) << endl;
            }
            break;
        }
        case 4:{
            CourseCatalog c;
            c.testCourseCatalog();
            break;
        }
        case 5:{
            CourseCatalog c;
            c.testCourseCatalog();
            c.saveCatalog();
            break;
        }
        case 6:{
            CourseCatalog c;
            c.loadCatalog();
            cout << c;
            break;
        }
        case 7:{
            bouncingBall();
            break;
        }
        default:
            cout << "Feilinput" << endl; 
            break;
    }
    return 0;
}



