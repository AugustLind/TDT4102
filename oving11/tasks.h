#pragma once
#include "Stopwatch.h"
#include <array>
#include "optimizationTask.h"
#include <random>

void task1();

void task2();

void task3();

void task4();

void task5();

void task6();

template<typename T>
T maximum(T lhs, T rhs){
    if (lhs >= rhs){
        return lhs;
    } else{
    return rhs;
    }
}

template<typename T>
T shuffle(T vec){
    std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<int> distribution(0, vec.size()-1);
    for (int i = 0; i < 10 ; i++){
        int a = (distribution(generator));
        int b = (distribution(generator));
        std::swap(vec.at(a),vec.at(b));
    }
    for (int i = 0; i < vec.size(); i++){
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
    return vec;
}

template<typename Type, int Size>

class MyArray{
    Type elements[Size];
public: 
    int getSize() const{
        return Size;
    };

    Type& at(int pos) {
        if (pos < 0 || pos >= Size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[pos];
    };

    void fill(Type value){
        for (int i = 0; i < Size; i++){
            elements[i] = value;
        }   
    }
};