CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g
all: SpinOut Unit
SpinOut: spinout_run.o spinout.o
	${CXX} ${CXXFLAGS} -o SpinOut spinout.o spinout_run.o
Unit: spinout_unit.o spinout.o
	${CXX} ${CXXFLAGS} -o $@ $^

# spinout_run.o: spinout.hpp
spinout.o: spinout.hpp
spinout_unit.o: spinout.hpp
