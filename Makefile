
2048: 2048.o modele.o
	clang++ -o 2048 2048.o modele.o -lncurses

2048.o: 2048.cpp
	clang++ -c 2048.cpp

modele.o: modele.cpp modele.hpp
	clang++ -c modele.cpp

clean:
	rm *.o 2048