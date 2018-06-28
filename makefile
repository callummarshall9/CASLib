hellomake: *.cpp
	g++ -c -g -pthread main.cpp
	g++ *.o -lpthread -o caslib
