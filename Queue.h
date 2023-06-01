//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_QUEUE_H
#define DESIGNPATTERNS2_QUEUE_H
#include <queue>
#include <condition_variable>
#include "iostream"
using namespace std ;
class Queue {
public:
    queue<void*> myQueue ;
    condition_variable cv ;
    mutex mtx ;
    bool condition ;
    Queue(){
        condition = false ;
    } ;
    Queue(Queue const &other){

    } ;

    void enQueue(void* element) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            myQueue.push(element);
            condition = true;
        }
        cv.notify_all();
        cout << "shitassBiatch!" << boolalpha << condition << endl;
    }

    void* deQueue() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return condition; });

        void* element = myQueue.front();
        myQueue.pop();
        condition = !myQueue.empty();
        lock.unlock();
        cv.notify_all();

        cout << "EMpty? " << boolalpha << myQueue.empty() << endl;

        return element;
    }
    void setCondition(bool val){
        condition = val ;
    }
};


#endif //DESIGNPATTERNS2_QUEUE_H
