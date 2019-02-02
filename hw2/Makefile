CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g

# Spinout: spinout_run.o spinout.o
# 	${CXX} ${CXXFLAGS} -o Spinout spinout.o spinout_run.o
Unit: spinout_unit.o spinout.o
	${CXX} ${CXXFLAGS} -o $@ $^

# spinout_run.o: spinout.hpp
spinout.o: spinout.hpp
spinout_unit.o: spinout.hpp
