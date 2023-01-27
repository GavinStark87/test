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
	addEdge(G, 2, 3);
	printf("test2\n");
	addEdge(G, 1, 4);
	printf("test3\n");
	addEdge(G, 3, 4);
	addEdge(G, 2, 4);
	addEdge(G, 1, 3);
	printf("test4\n");
	int x = 1;
	printf("%d\n", G->color[x]);
	moveFront(G->neighbors[x]);
	while (index(G->neighbors[x]) != -1 && !isEmpty(G->neighbors[x]))
	{
		printf("neighbor%d\n", get(G->neighbors[x]));
		moveNext(G->neighbors[x]);
	}
	
	freeGraph(&G);
	printf("test5\n");
}