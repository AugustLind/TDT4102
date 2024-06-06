#include "tasks.h"    

void task1(){    
    Stopwatch watch;
   
    constexpr int size = 10000;
    constexpr int rounds = 1000000;

    watch.start();
    for (int i = 0; i < rounds; i++){
        // Stack allocation
        //std::array<int, size> arr1;

        //Heap allocation
        //std::array<int, size>* arr2 = new std::array<int,size>;
        //delete arr2;
    
        //Stack allocation er mye raskerer
    }

    std::cout << "It took " << watch.stop() << " seconds" << std::endl;
}

void task2() {

    /*
    //Oppgace 2 a, b , c

    std::vector<int> numbers;
    
    //numbers.reserve(20);
    //når jeg bruker reserve starter capacity på 20 istedenfor å endre seg når jeg legger inn flere elementer
    
    numbers.resize(20);
    std::cout << "Start Size: " << numbers.size() << std::endl;
    std::cout << "Start Capacity: " << numbers.capacity() << std::endl;
    //da er sizen startet på 20 og i løepn blir det lagt inn flere verdier, capacity starter på 20 og øker til 40
    //hvis vi skal få samme vektor som i a) må koden endres
    for (int i = 0; i < 20; i++){
        numbers.push_back(i);
        std::cout << "Size: " << numbers.size() << std::endl;
        std::cout << "Capacity: " << numbers.capacity() << std::endl;
    */
    std::vector<int> numbers;
    
    Stopwatch watch;
    watch.start();
     for (int i = 0; i < 1000000; i++){
        numbers.push_back(i);
    }
    std::cout << "Time without optimization " << watch.stop() << std::endl;

    std::vector<int> numbers2;
    numbers2.reserve(1000000);

    watch.start();
     for (int i = 0; i < 1000000; i++){
        numbers2.push_back(i);
    }
    std::cout << "Time with reserve " << watch.stop() << std::endl;

    std::vector<int> numbers3;
    numbers2.resize(1000000);

    watch.start();
     for (int i = 0; i < 1000000; i++){
        numbers3.push_back(i);
    }
    std::cout << "Time with resize " << watch.stop() << std::endl;

    //Vi ser at reserve er raskest og resize er tregest.
}

void task3(){
    Stopwatch watch;
    watch.start();
    optimizationTask();
    std::cout << "Time without optimization " << watch.stop() << std::endl;
    //Time without optimization 11.5019
    //Time with my optimizations 7.19551
}

void task4(){
    int a = 1;
    int b = 2;
    int c = maximum<int>(a, b);
    std::cout << c << std::endl;
    // c er nå 2.
    double d = 2.4;
    double e = 3.2;
    double f = maximum<double>(d,e);
    std::cout << f << std::endl;
}

void task5(){
    std::vector<int> a{1, 2, 3, 4, 5, 6, 7};
    shuffle(a); // Resultat, rekkefølgen i a er endret.
    std::vector<double> b{1.2, 2.2, 3.2, 4.2};
    shuffle(b); // Resultat, rekkefølgen i b er endret.
    std::vector<std::string> c{"one", "two", "three", "four"};
    shuffle(c); // Resultat, rekkefølgen i c er endret.
}

void task6(){
     // Oppretter et MyArray-objekt for int med 5 elementer
    MyArray<int, 5> intArray;
    intArray.fill(10);  // Fyller med verdien 10
    std::cout << "Int array: ";
    for (int i = 0; i < intArray.getSize(); i++) {
        std::cout << intArray.at(i) << " ";
    }
    std::cout << "\n";

    // Oppretter et MyArray-objekt for double med 3 elementer
    MyArray<double, 3> doubleArray;
    doubleArray.fill(3.14);  // Fyller med verdien 3.14
    std::cout << "Double array: ";
    for (int i = 0; i < doubleArray.getSize(); i++) {
        std::cout << doubleArray.at(i) << " ";
    }
    std::cout << "\n";

    // Tester aksess utover grensene og fanger opp unntak
    try {
        std::cout << "Test utenfor grense: " << intArray.at(5) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Unntak fanget: " << e.what() << "\n";
    }
}