//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_QUEUE_HPP
#define DESIGNPATTERNS2_QUEUE_HPP
#include <queue>
#include <condition_variable>
#include <atomic>
#include "iostream"
using namespace std ;
static int index = 0 ;
class Queue {
public:
    queue<void*> myQueue ;
    condition_variable cv ;
    mutex mtx ;
    std::unique_lock<std::mutex> lock ;
    int num ;
    Queue() ;
    Queue(Queue const &other) ;

    void enQueue(void* element) ;

    void* deQueue() ;
};


#endif //DESIGNPATTERNS2_QUEUE_HPP
