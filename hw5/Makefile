CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Yahtzee: yahtzee.o game.cpp
	${CXX} ${CXXFLAGS} -o $@ $^

yahtzee.o: yahtzee.hpp yahtzee.cpp
