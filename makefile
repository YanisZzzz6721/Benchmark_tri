CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

run: main
	./main

clean:
	rm -f main