#include "st_pipeline.hpp"
st_pipeline::st_pipeline(int n, int seed) : n(n), seed(seed){
    objects.reserve(4) ;
    objects.push_back(ActiveObject::CreateActiveObject(&func0)) ;
    objects.push_back(ActiveObject::CreateActiveObject(&func1)) ;
    objects.push_back(ActiveObject::CreateActiveObject(&func2)) ;
    objects.push_back(ActiveObject::CreateActiveObject(&func3)) ;
    objects[0]->next = objects[1] ;
    objects[1]->next = objects[2] ;
    objects[2]->next = objects[3] ;
    auto newTask = new ActiveObject::Task(&n, objects[1], &seed) ;
    objects[0]->getQueue().enQueue(newTask) ;
    for (auto& obj : objects) {
        obj->myThread.join();
    }

}

void printUsage(){
    cout << "Wrong format." << endl << "Please use by one of the following formats: " << endl <<
         "1.    ./st_pipeline <N> <random seed>" << endl <<
         "2.    ./st_pipeline <N>" << endl << "*Note that arguments should be integers." << endl ;
}

int main(int argc, char* argv[]){
    if(argc > 3 || argc < 2){
        printUsage() ;
        return -1 ;
    }
    int N, seed ;
    try {
        N = stoi(argv[1]);
        if(argc == 3) {
            seed = stoi(argv[2]);
        }else{
            std::time_t currentTime = std::time(nullptr);
            seed = static_cast<int>(currentTime);
        }
    } catch (exception &e) {
        printUsage() ;
        return -1 ;
    }
    st_pipeline(N, seed) ;
}