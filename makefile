
CXX=g++
FLAGS=-std=c++0x -Wall

SOURCE=main.cpp utils.cpp

.PHONY:all
all:
	$(CXX) $(FLAGS) -o main.out $(SOURCE) -lrt

.PHONY:clean
clean:
	rm -f main

