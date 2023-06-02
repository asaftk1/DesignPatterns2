//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_QUEUE_H
#define DESIGNPATTERNS2_QUEUE_H
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
    std::atomic<bool> condition ;
    int num ;
    Queue(){
        num = index++ ;
        condition = false ;
    } ;
    Queue(Queue const &other){

    } ;

    void enQueue(void* element) {
        myQueue.push(element);
        cv.notify_all();
//        cout << "Enqueued to q number " << num << " Size: " << myQueue.size() << endl;
    }

    void* deQueue() {
//        cout << "Queue " << num << "waiting with size: " << myQueue.size() << endl ;
        lock = std::unique_lock<std::mutex>(mtx);
        cv.wait(lock, [this] {
            return !myQueue.empty() ;
        });
//        cout << "Continue with queue: " << num << endl ;
        void* element = myQueue.front();
        myQueue.pop();
        lock.unlock() ;
        return element;
    }
    void setCondition(bool val){
        condition = val ;
    }
};


#endif //DESIGNPATTERNS2_QUEUE_H
