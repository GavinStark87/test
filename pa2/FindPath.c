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
	addEdge(G,2, 3);
	addEdge(G,1, 4);
	addEdge(G,3, 4);
	freeGraph(&G);
}