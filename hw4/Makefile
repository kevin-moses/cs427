CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Maze: maze.o
	${CXX} ${CXXFLAGS} -o $@ $^

maze.o: maze.cpp maze.hpp main.cpp
