//
// Created by ts on 6/1/23.
//

#ifndef DESIGNPATTERNS2_ST_PIPELINE_HPP
#define DESIGNPATTERNS2_ST_PIPELINE_HPP
#include "ActiveObject.hpp"
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
    st_pipeline(int n, int seed) ;
};


#endif //DESIGNPATTERNS2_ST_PIPELINE_HPP
