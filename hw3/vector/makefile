CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17 -g

Test: vector_test.o task.o
	${CXX} ${CXXFLAGS} -o $@ $^

vector_test.o: vector.hpp task.hpp vector.cpp
task.o: task.hpp