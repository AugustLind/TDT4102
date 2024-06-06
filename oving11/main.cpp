#include "tasks.h"


int main() {
    
    std::cout << "Task 1" << std::endl;
    std::cout << "Task 2" << std::endl;
    std::cout << "Task 3" << std::endl;
    std::cout << "Task 5" << std::endl;

    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        task1();
        break;
    case 2:
        task2();
        break;
    case 3:
        task3();
        break;
    case 4:
        task4();
        break;
    case 5:
        task5();
        break;
    case 6:
        task6();
        break;
    default:
        break;
    }
    return 0;
}



