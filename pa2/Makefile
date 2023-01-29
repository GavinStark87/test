#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make GraphTest2           makes GraphTest2
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

DEBUG ?= 0

ifeq ($(DEBUG), 1)
		COMPILE += -g  -gdwarf-4
endif

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphTest2 : GraphTest2.o $(BASE_OBJECTS)
	$(LINK) GraphTest2 GraphTest2.o $(BASE_OBJECTS)

ListTest : ListTest.o $(BASE_OBJECTS)
	$(LINK) ListTest ListTest.o $(BASE_OBJECTS)

#Graph.o : Graph.c Graph.h
#	$(COMPILE) Graph.c

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

GraphTest2.o : GraphTest2.c $(HEADERS)
	$(COMPILE) GraphTest2.c

ListTest.o : ListTest.c $(HEADERS)
	$(COMPILE) ListTest.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphClient GraphTest GraphTest2 FindPath.o GraphClient.o GraphTest.o GraphTest2.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in7 junk7

checkClient : GraphClient
	$(MEMCHECK) GraphClient