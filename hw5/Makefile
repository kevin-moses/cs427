CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Yahtzee: diceroll.o rule.o yahtzee.o factory.o game.cpp
	${CXX} ${CXXFLAGS} -o $@ $^
diceroll.o: diceroll.hpp diceroll.cpp
rule.o: rule.hpp rule.cpp diceroll.hpp
yahtzee.o: yahtzee.hpp yahtzee.cpp rule.hpp diceroll.hpp
factory.o: factory.hpp factory.cpp yahtzee.hpp rule.hpp diceroll.hpp
