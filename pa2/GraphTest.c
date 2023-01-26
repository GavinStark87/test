/*
Gavin Stark
gestark
pa2
*/
#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv){
	Graph G = newGraph(5);
	printf("test1\n");
	//addEdge(G, 2, 3);
	printf("test2\n");
	//addEdge(G, 1, 4);
	printf("test3\n");
	//addEdge(G, 3, 4);
	printf("test4\n");

	freeGraph(&G);
	printf("test5\n");
}