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
	Graph D = newGraph(5);
	List L = newList();
	printf("%d\n", getOrder(G));
	printf("%d\n", getSize(G));
	FILE* out = fopen("out.txt", "w");
	FILE* in = fopen("in1.txt", "r");
	addEdge(G, 2, 3);
	addEdge(G, 1, 4);
	addEdge(G, 3, 4);
	addEdge(G, 2, 4);
	addEdge(G, 1, 3);
	addEdge(G, 5, 1);
	//addEdge(G, 6, 2); appropriately errored out
	//addEdge(G, 0, 1); appropriately errored out
	printf("%d\n", getOrder(G));
	printf("%d\n", getSize(G));
	printf("%d\n", getSource(G));
	BFS(G, 1);
	printf("%d\n", getSource(G));
	printf("%d\n", getParent(G, 2));
	printf("%d\n", getDist(G, 2));
	getPath(L, G, 2);
	printfList(L);
	printGraph(out, G);
	makeNull(G);
	printGraph(out, G);

	addArc(D, 2, 3);
	addArc(D, 1, 4);
	addArc(D, 3, 4);
	addArc(D, 2, 4);
	addArc(D, 1, 3);
	addArc(D, 5, 1);
	//addArc(D, 6, 2); appropriately errored out
	//addArc(D, 0, 1); appropriately errored out
	printf("%d\n", getOrder(D));
	printf("%d\n", getSize(D));
	printf("%d\n", getSource(D));
	BFS(D, 1);
	printf("%d\n", getSource(D));
	printf("%d\n", getParent(D, 2));
	printf("%d\n", getDist(D, 2));
	getPath(L, D, 2);
	printfList(L);
	printGraph(out, D);
	makeNull(D);
	printGraph(out, D);
	
	printGraph(out, D);
	fclose(out);
	fclose(in);
	freeList(&L);
	freeGraph(&D);
	freeGraph(&G);
}