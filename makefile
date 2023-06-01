CXX=clang++-14

all: main

main: main.cpp st_pipeline
	$(CXX) -o main main.cpp -pthread

st_pipeline: st_pipeline.h ActiveObject
	$(CXX) -o st_pipeline st_pipeline.h

ActiveObject: ActiveObject.h Queue
	$(CXX) -o ActiveObject ActiveObject.h

Queue: Queue.h
	$(CXX) -o Queue Queue.h