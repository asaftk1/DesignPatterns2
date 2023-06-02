#include "Queue.hpp"
Queue::Queue(){
    num = index++ ;
} ;
Queue::Queue(Queue const &other): myQueue(other.myQueue), num(other.num) {

} ;

void Queue::enQueue(void* element) {
    myQueue.push(element);
    cv.notify_all();
//        cout << "Enqueued to q number " << num << " Size: " << myQueue.size() << endl;
}

void* Queue::deQueue() {
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