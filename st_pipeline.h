//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_ST_PIPELINE_H
#define DESIGNPATTERNS2_ST_PIPELINE_H
#include "ActiveObject.h"
#include <vector>
#include <random>
#include <iostream>

using namespace std;

class st_pipeline {
public:
    vector<ActiveObject*> objects ;
    int n ;
    int seed ;
    std::mt19937_64 rng ;
    st_pipeline(int n, int seed) : n(n), seed(seed){
        objects.reserve(4) ;
        objects.push_back(ActiveObject::CreateActiveObject(&func0)) ;
        objects.push_back(ActiveObject::CreateActiveObject(&func1)) ;
        objects.push_back(ActiveObject::CreateActiveObject(&func2)) ;
        objects.push_back(ActiveObject::CreateActiveObject(&func3)) ;
        objects[0]->next = objects[1] ;
        objects[1]->next = objects[2] ;
        objects[2]->next = objects[3] ;
        auto newTask = new ActiveObject::Task(&n, objects[1], &seed) ;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        objects[0]->getQueue().enQueue(newTask) ;
        objects[0]->getQueue().setCondition(true) ;
    }
};


#endif //DESIGNPATTERNS2_ST_PIPELINE_H
