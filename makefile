INCLUDE = SplayTree.h SNode.h

all : prog1

prog1: main.o
	g++ main.o -o prog2

main.o: main.cpp $(INCLUDE)
	g++ -c -g main.cpp

clean:
	rm -f *.o prog2