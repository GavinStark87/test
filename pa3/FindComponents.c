#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10

int main(int argc, char **argv){
	if(argc < 3){
		
		printf("FindComponents Error: calling FindComponents with too few arguements.\n");
		exit(EXIT_FAILURE);
	} else if(argc > 3){
		
		printf("FindComponents Error: calling FindComponents with too many arguements.\n");
		exit(EXIT_FAILURE);
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if(in == NULL){
		printf("FindComponents Error: input file not found.\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL){
		printf("FindComponents Error: output file not found.\n");
		exit(EXIT_FAILURE);
	}
	char* array = calloc((MAX_LINE_LENGTH), sizeof(char));
	fgets(array, MAX_LINE_LENGTH, in);
	int c = atoi(array);
	
	Graph G = newGraph(c);
	fgets(array, MAX_LINE_LENGTH, in);
	fprintf(out, "Adjacency list representation of G:\n");
	int number;
	int otherNumber;
	while(array[0] != '0'){
		number = atoi(array);
		for(int i = 0; i < MAX_LINE_LENGTH; i++){
			if(array[i] == ' '){
				otherNumber = atoi(&(array[i]));
				break;
			}
		}
		printf("%d %d\n", number, otherNumber);
		addArc(G, number, otherNumber);
		fgets(array, MAX_LINE_LENGTH, in);
	}
	printGraph(out, G);
	fprintf(out, "\n");
	fgets(array, MAX_LINE_LENGTH, in);
	List S = newList();
	for(int i = 1; i < getOrder(G) + 1; i++){
		append(S, i);
	}
	List L = newList();
	Graph Gt = transpose(G);
	DFS(G, S);
	DFS(Gt, S);
	int numComponents = 0;
	moveFront(S);
	while(S != NULL && index(S) != -1){
		if(getParent(Gt, get(S)) == NIL){
			numComponents++;
		}
		moveNext(S);
	}
	fprintf(out, "G contains %d strongly connected components:\n", numComponents);
	int comp = 1;
	moveBack(S);
	while(S != NULL && index(S) != -1){
		if(getParent(Gt, get(S)) == NIL){
			prepend(L, get(S));
			fprintf(out, "Component %d: ", comp);
			printList(out, L);
			fprintf(out, "\n");
			clear(L);
			comp++;
		} else {
			prepend(L, get(S));
		}
		movePrev(S);
		
	}
	//printf("%d\n", G->colors);
	freeList(&L);
	freeList(&S);
	free(array);
	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeGraph(&Gt);
}