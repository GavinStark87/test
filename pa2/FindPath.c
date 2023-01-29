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

#define MAX_LINE_LENGTH 10

int main(int argc, char **argv){
	if(argc < 3){
		
		printf("Lex Error: calling Lex with too few arguements.\n");
		exit(EXIT_FAILURE);
	} else if(argc > 3){
		
		printf("Lex Error: calling Lex with too many arguements.\n");
		exit(EXIT_FAILURE);
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Lex Error: input file not found.\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL){
		printf("Lex Error: output file not found.\n");
		exit(EXIT_FAILURE);
	}
	char* array = calloc((MAX_LINE_LENGTH), sizeof(char));
	fgets(array, MAX_LINE_LENGTH, in);
	int c = atoi(array);
	
	Graph G = newGraph(c);
	fgets(array, MAX_LINE_LENGTH, in);
	
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
		addEdge(G, number, otherNumber);
		fgets(array, MAX_LINE_LENGTH, in);
	}
	printGraph(out, G);
	fprintf(out, "\n");
	fgets(array, MAX_LINE_LENGTH, in);
	List L = newList();
	while(array[0] != '0'){
		number = atoi(array);
		for(int i = 0; i < MAX_LINE_LENGTH; i++){
			if(array[i] == ' '){
				otherNumber = atoi(&(array[i]));
				break;
			}
		}
		BFS(G, number);
		
		
		getPath(L, G, otherNumber);
		if(back(L) == NIL){
			fprintf(out, "The distance from %d to %d is infinity\n", number, otherNumber);
			fprintf(out, "No %d-%d path exists\n",number, otherNumber);
		} else {
			fprintf(out, "The distance from %d to %d is %d\n", number, otherNumber, getDist(G, otherNumber));
			fprintf(out, "A shortest %d-%d path is: ", number, otherNumber);
			printList(out, L);
			fprintf(out, "\n");
		}
		clear(L);
		fprintf(out, "\n");
		fgets(array, MAX_LINE_LENGTH, in);
	}
	
	
	//printf("%d\n", G->colors);
	freeList(&L);
	free(array);
	fclose(in);
	fclose(out);
	freeGraph(&G);
}