all: graph.exe

graph.exe: main.o graph.o
	g++ main.o graph.o -o graph.exe

main.o: main.cpp graph.hpp
	g++ -c main.cpp -o main.o

graph.o: graph.cpp graph.hpp
	g++ -c graph.cpp -o graph.o

run: graph.exe
	./graph.exe
