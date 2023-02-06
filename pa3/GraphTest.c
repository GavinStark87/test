#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
	Graph G = newGraph(8);
	FILE* out = fopen(argv[1], "w");
	List L = newList();
	append(L, 1);
	append(L, 2);
	append(L, 3);
	append(L, 4);
	append(L, 5);
	append(L, 6);
	append(L, 7);
	append(L, 8);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 3, 4);
	addArc(G, 3, 5);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 5, 1);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	addArc(G, 7, 6);
	addArc(G, 8, 8);
	printf("test1\n");
	printGraph(out, G);
	printf("test2\n");
	DFS(G, L);
	printf("test3\n");
	printfList(L);
	printf("test4\n");
	for (int i = 1; i < getOrder(G) + 1; i++){
		printf("finish order %d %d\n", getFinish(G, i), i);
	}
	Graph H = transpose(G);
	printf("test5\n");
	printGraph(out, H);
	printf("test6\n");
	

