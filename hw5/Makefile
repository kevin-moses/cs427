CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

Yahtzee: diceroll.o rule.o yahtzee.o factory.o game.o
	${CXX} ${CXXFLAGS} -o $@ $^

diceroll.o: diceroll.hpp
rule.o: rule.hpp diceroll.hpp
yahtzee.o: yahtzee.hpp rule.hpp diceroll.hpp
factory.o: factory.hpp yahtzee.hpp rule.hpp
