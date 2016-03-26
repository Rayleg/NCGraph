CXX=g++
SRC=graph.cpp
CXXFLAGS=-g -Wall

graph: graph.cpp
	$(CXX) $(SRC) $(CXXFLAGS) -o graph

