#build
Run: programa.o
	g++ programa.o -o Run -lncurses

#Programa
programa.o: programa.cpp
	g++ -c programa.cpp
