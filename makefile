Yahtzee.x : main.cpp Die.o
	g++ main.cpp Die.o -o Yahtzee.x

Die.o : Die.cpp Die.hpp
	g++ -c Die.cpp

clean : 
	rm *~ Yahtzee.x *.o