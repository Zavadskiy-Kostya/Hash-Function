prog: main.o 
	g++ main.o -o prog

clean:
	rm -f *.o prog
	rm -f *.out

main.o: main.cpp Hash.hpp
	g++ -c main.cpp



