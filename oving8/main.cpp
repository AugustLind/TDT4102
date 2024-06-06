#include "utilities.h"
#include <iostream>
#include "dummy.h"

int main() {
    
    int choice{0};
    std::cout << "1) Fibonacci-rekken" << std::endl;
    std::cout << "2) Sjekke medlemsklassen Matrix" << std::endl;
    std::cout << "3) Dummytest" << std::endl;
    std::cout << "4) Deep-copy" << std::endl;
    std::cout << "5) Matrisesummering" << std::endl;
    std::cin >> choice;
    switch (choice) {
        case 1: {
            createFibonacci();
            break;
        }
        case 2: {
            Matrix a{4};
            Matrix b{4,3};
            b.set(3,1,2);
            std::cout << a << std::endl;
            std::cout << b;
            Matrix A{4};
            std::cout << A[0][2] << ", " << A[3][3];
            break;
        }
        case 3: {
            dummyTest();
            break;
        }
        case 4: {
            Matrix a(3, 4);
            a.set(2,1,5);
            Matrix b = a;
            b.set(1, 2, 10);  
            a.set(2,2,10);
            std::cout << "Matrix a:" << std::endl;
            std::cout << a << std::endl;
            std::cout << "Matrix b:" << std::endl;
            std::cout << b << std::endl;
            break;
        }
        case 5: {
            Matrix a(2, 2);
            Matrix b(2, 2);
            Matrix c(2, 2);
            a.set(0, 0, 1);
            a.set(0, 1, 2);
            a.set(1, 0, 3);
            a.set(1, 1, 4);
            b.set(0, 0, 4);
            b.set(0, 1, 3);
            b.set(1, 0, 2);
            b.set(1, 1, 1);
            c.set(0, 0, 1);
            c.set(0, 1, 3);
            c.set(1, 0, 1.5);
            c.set(1, 1, 2);
            a += b;
            a += c;
            std::cout << "Matrix a:" << std::endl;
            std::cout << a << std::endl;
            std::cout << "Matrix b:" << std::endl;
            std::cout << b << std::endl;
            std::cout << "Matrix c:" << std::endl;
            std::cout << c << std::endl;
            std::cout << b + c << std::endl;
            break;
        }
        default:
            std::cout << "Feilinput" << std::endl; 
            break;
    }
    return 0;
}
