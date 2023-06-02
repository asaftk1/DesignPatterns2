//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_ACTIVEOBJECT_HPP
#define DESIGNPATTERNS2_ACTIVEOBJECT_HPP
#include "Queue.hpp"
#include <thread>
#include "random"
#include <iostream>

using namespace std;
class ActiveObject {
private:
    Queue myQueue ;
    bool isOn ;
    void (*functionPtr)(void*);

public:
    thread myThread ;

    class Task{
    public:
        Task(int* num, ActiveObject* next, int* seed = nullptr) ;
        ActiveObject* next ;
        int* num ;
        int* seed ;

    };

    ActiveObject* next ;

    ActiveObject(void (*func)(void*)) ;

    void busyLoop() ;

    Queue& getQueue() ;

    static ActiveObject* CreateActiveObject(void (*func)(void*)) ;

    static void stop(ActiveObject*) ;
};

int* generateRandomNumbers(std::mt19937_64* rng) ;


int isPrime(int num) ;

void func0(void* arg) ;

void func1(void* arg) ;

void func2(void* arg) ;

void func3(void* arg) ;

#endif //DESIGNPATTERNS2_ACTIVEOBJECT_HPP
