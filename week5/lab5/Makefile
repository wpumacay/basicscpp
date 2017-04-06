
all : test-maze genmaze

test-maze : test-maze.o maze.o testbase.o
	g++ -std=c++14 -Wall test-maze.o maze.o testbase.o -o test-maze.out

genmaze : genmaze.o maze.o
	g++ -std=c++14 -Wall genmaze.o maze.o -o genmaze.out

genmaze.o : genmaze.cc maze.cc
	g++ -std=c++14 -Wall -c genmaze.cc maze.cc

maze.o : maze.cc maze.hh
	g++ -std=c++14 -Wall -c maze.cc

testbase.o : testbase.cc testbase.hh
	g++ -std=c++14 -Wall -c testbase.cc

test-maze.o : test-maze.cc
	g++ -std=c++14 -Wall -c test-maze.cc

clean :
	rm -f *.out *.o *~
