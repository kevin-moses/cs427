CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Maze: maze.o main.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

maze.o: maze.hpp maze.cpp
