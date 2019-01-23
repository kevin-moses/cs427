CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17

Distance: distance.o geometry.o
	${CXX} ${CXXFLAGS} -o Distance distance.o geometry.o

distance.o: geometry.hpp
geometry.o: geometry.hpp