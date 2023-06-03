#include "ActiveObject.hpp"
ActiveObject::Task::Task(int *num, ActiveObject *next, int *seed) : num(num), next(next), seed(seed) {}

ActiveObject::ActiveObject(void (*func)(void *)) : functionPtr(func), myThread(&ActiveObject::busyLoop, this), next(nullptr), isOn(true)
{
}

void ActiveObject::busyLoop()
{
    void *task;
    while ((task = this->myQueue.deQueue()))
    {
        functionPtr(task);
    }
    
}

Queue &ActiveObject::getQueue()
{
    return myQueue;
}

ActiveObject *ActiveObject::CreateActiveObject(void (*func)(void *))
{
    return new ActiveObject(func);
}

void ActiveObject::stop(ActiveObject* activeObject) {
    Task* t = new Task(nullptr, nullptr);
    activeObject->isOn = false;
    activeObject->getQueue().enQueue(t);
}

void ActiveObject::stopAll() {
    ActiveObject* current = this;
    while (current != nullptr) {
        ActiveObject* next = current->next;
        stop(current);
        current = next;
        
        // Wait for a brief moment to allow tasks to complete
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    // Delete the objects after stopping them
    current = this;
    while (current != nullptr) {
        ActiveObject* next = current->next;
        delete current;
        current = next;
    }
    
    exit(0);
}
int *generateRandomNumbers(std::mt19937_64 *rng)
{
    std::uniform_int_distribution<int> distribution(100000, 999999); // Range of 6-digit numbers
    return new int(distribution(*rng));
}

int isPrime(int num)
{
    if (num < 1)
    {
        return 0;
    }
    else if (num <= 3)
    {
        return true;
    }
    else
    {
        for (int i = 2; i <= sqrt(num); i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}

void func0(void *arg)
{
    ActiveObject::Task *task = static_cast<ActiveObject::Task *>(arg);
    if (task->next == nullptr || task->next->next == nullptr)
    {
        delete task;
        return;
    }
    std::mt19937_64 rng(*task->seed);
    int *currentNum;
    for (int i = 0; i < *task->num; ++i)
    {
        currentNum = generateRandomNumbers(&rng);
        ActiveObject::Task *newTask = new ActiveObject::Task(currentNum, task->next->next, nullptr);
        task->next->getQueue().enQueue(newTask);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    ActiveObject::Task *newTask = new ActiveObject::Task(nullptr, task->next->next, nullptr);
    task->next->getQueue().enQueue(newTask);
    delete task;
}

void func1(void *arg)
{
    ActiveObject::Task *task = static_cast<ActiveObject::Task *>(arg);
    if (task->num == nullptr)
    {
        task->next->stopAll();   
    }
    cout << *task->num << endl
         << (isPrime(*task->num) ? "True" : "False") << endl;
    *task->num += 11;
    
    ActiveObject::Task *newTask = new ActiveObject::Task(task->num, task->next->next, nullptr);
    task->next->getQueue().enQueue(newTask);
    delete task;
}

void func2(void *arg)
{
    ActiveObject::Task *task = static_cast<ActiveObject::Task *>(arg);
     if (task->num == nullptr)
    {
         task->next->stopAll();  
        // exit(0);
    }
    cout << *task->num << endl
         << (isPrime(*task->num) ? "True" : "False") << endl;
    *task->num -= 13;
    ActiveObject::Task *newTask = new ActiveObject::Task(task->num, task->next->next, nullptr);
    task->next->getQueue().enQueue(newTask);
    delete task;
}

void func3(void *arg)
{
    ActiveObject::Task *task = static_cast<ActiveObject::Task *>(arg);
    if (task->num == nullptr)
    {
         task->next->stopAll();  
        // exit(0);
    }
    cout << *task->num << endl;
    *task->num += 2;
    cout << *task->num << endl;

    cout <<  endl;
    delete task;
}
