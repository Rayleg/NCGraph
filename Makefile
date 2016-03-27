CXX=g++
SRC=graph.cpp
CXXFLAGS=-g -Wall

graph: graph.cpp
	$(CXX) $(SRC) $(CXXFLAGS) -o graph
test: test_gen.cpp
	$(CXX) $(CXXFLAGS) test_gen.cpp -o testgen
