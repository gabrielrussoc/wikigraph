CXX=g++
CXXFLAGS=-std=c++11 -O2

shell:
	$(CXX) $(CXXFLAGS) src/cpp/test.cpp src/cpp/wiki_graph.cpp src/cpp/wiki_graph.hpp -o shell

