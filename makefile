CXX=clang++-14

all: st_pipeline

st_pipeline: st_pipeline.o ActiveObject.o Queue.o
	$(CXX) -o st_pipeline st_pipeline.o ActiveObject.o Queue.o -pthread

st_pipeline.o: st_pipeline.cpp st_pipeline.hpp ActiveObject.o
	$(CXX) -c st_pipeline.cpp -o st_pipeline.o

ActiveObject.o: ActiveObject.hpp ActiveObject.cpp Queue.o
	$(CXX) -c ActiveObject.cpp -o ActiveObject.o

Queue.o: Queue.hpp Queue.cpp
	$(CXX) -c Queue.cpp -o Queue.o

clean:
	rm -f st_pipeline st_pipeline.o ActiveObject.o Queue.o