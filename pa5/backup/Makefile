#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

COMPILE = g++ -std=c++17 -Wall -c
DEBUG ?= 0

ifeq ($(DEBUG), 1)
	COMPILE += -g -gdwarf-4
endif

Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o : List.h Shuffle.cpp
	$(COMPILE) Shuffle.cpp

ListClient : ListClient.o List.o
	g++ -std=c++17 -Wall -o ListClient ListClient.o List.o 

ListClient.o : List.h ListClient.cpp
	$(COMPILE) ListClient.cpp

List.o : List.h List.cpp
	$(COMPILE) List.cpp

clean :
	rm -f Shuffle Shuffle.o ListClient ListClient.o List.o

check1 : ListClient
	valgrind --leak-check=full ListClient

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35