#include "std_lib_facilities.h"
#include "utilities.h"

/*
1a) Public kan bli "acsessa" fra utsiden av klassen
Private kan ikke bli "acsessa eller sette" fra andre en klassen
Protected kan bli brukt av arv classer.


int main() {
    int choice{0};
    cin >> choice;
    switch (choice) {
        case 1: {
            testAnimal();
            break;
        }
        default:
            cout << "Feilinput" << endl; 
            break;
    }
    return 0;
}

*/