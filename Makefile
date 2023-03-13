

networkmap:	Main.o
	g++	Main.o	-o networkmap

Main.o:
	g++ -std=c++11	-c Main.cpp -o Main.o

