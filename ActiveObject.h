//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_ACTIVEOBJECT_H
#define DESIGNPATTERNS2_ACTIVEOBJECT_H
#include "Queue.h"
#include <thread>
#include "random"
#include <iostream>

using namespace std;
class ActiveObject {
private:
    Queue myQueue ;
    void (*functionPtr)(void*);
public:
    thread myThread ;

    class Task{
    public:
        Task(int* num, ActiveObject* next, int* seed = nullptr): num(num), next(next), seed(seed) {}
        ActiveObject* next ;
        int* num ;
        int* seed ;

    };
    ActiveObject* next ;

    ActiveObject(void (*func)(void*)): functionPtr(func), myThread(&ActiveObject::busyLoop, this), next(nullptr){
    }

    void busyLoop(){
        void* task ;
        while((task=this->myQueue.deQueue())) {
            functionPtr(task);
        }
    }




    Queue& getQueue(){
        return myQueue ;
    }

    static ActiveObject* CreateActiveObject(void (*func)(void*)) {
        return new ActiveObject(func) ;
    }
};

int* generateRandomNumbers(std::mt19937_64* rng) {
    std::uniform_int_distribution<int> distribution(100000, 999999);  // Range of 6-digit numbers
    return new int(distribution(*rng));
}


int isPrime(int num){
    if(num < 1){
        return 0 ;
    }else if(num <= 3){
        return true ;
    }else{
        for(int i = 2 ; i <= sqrt(num) ; i++){
            if(num%i == 0){
                return false ;
            }
        }
        return true ;
    }
}

void func0(void* arg){
    ActiveObject::Task* task = static_cast<ActiveObject::Task*>(arg) ;
    cout << "func 0! n: " << *task->num << " seed: " << *task->seed << endl ;
    std::mt19937_64 rng(*task->seed) ;
    int* currentNum ;
    for (int i = 0; i < *task->num; ++i) {
        currentNum = generateRandomNumbers(&rng) ;
        cout << "Generated number: " << *currentNum << endl ;
        ActiveObject::Task* newTask = new ActiveObject::Task(currentNum, task->next->next, nullptr) ;
        task->next->getQueue().enQueue(newTask) ;
        std::this_thread::sleep_for(std::chrono::milliseconds (1));
    }
}

void func1(void* arg){
    cout << "func 1! " << endl ;
    ActiveObject::Task* task = static_cast<ActiveObject::Task*>(arg) ;
    cout << *task->num << endl << boolalpha << isPrime(*task->num) << endl ;
    *task->num += 11 ;
    ActiveObject::Task* newTask = new ActiveObject::Task(task->num, task->next->next, nullptr) ;
    task->next->getQueue().enQueue(newTask) ;

}

void func2(void* arg){
    cout << "func 2! " << endl ;
    ActiveObject::Task* task = static_cast<ActiveObject::Task*>(arg) ;
    cout << *task->num << endl << boolalpha << isPrime(*task->num) << endl ;
    *task->num -= 13 ;
    ActiveObject::Task* newTask = new ActiveObject::Task(task->num, task->next->next, nullptr) ;
    task->next->getQueue().enQueue(newTask) ;

}

void func3(void* arg){
    cout << "func 3! " << endl ;
    ActiveObject::Task* task = static_cast<ActiveObject::Task*>(arg) ;
    cout << *task->num << endl ;
    *task->num += 2 ;
    cout << *task->num << endl ;
}

#endif //DESIGNPATTERNS2_ACTIVEOBJECT_H
