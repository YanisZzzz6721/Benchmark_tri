CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

main: main.cpp sorters.cpp mesure.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp sorters.cpp mesure.cpp

run: main
	./main

clean:
	rm -f main