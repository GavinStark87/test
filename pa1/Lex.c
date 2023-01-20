/*
Gavin Stark
gestark
pa1
*/
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 300

int main(int argc, char **argv){

	if(argc < 3){
		
		printf("Lex Error: calling Lex with too few arguements.\n");
		exit(EXIT_FAILURE);
	} else if(argc > 3){
		
		printf("Lex Error: calling Lex with too many arguements.\n");
		exit(EXIT_FAILURE);
	}
	List L = newList();
	char** array;
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
	
	int numLines = 1;
	for(char c = getc(in); c != EOF; c = getc(in)){
		if(c == '\n'){
			numLines++;
		}
	}
	array = (char **)calloc(numLines, sizeof(char *));
	rewind(in);
	for(int i = 0; i < numLines; i++){
		array[i] = (char *)calloc((MAX_LINE_LENGTH), sizeof(char *));
		fgets(array[i], MAX_LINE_LENGTH, in);
	}
	
	int lastchar = 0;
	while (true)
	{
		if(array[numLines -1][lastchar] == '\0'){
			array[numLines -1][lastchar] = '\n';
			array[numLines -1][lastchar + 1] = '\0';
			break;
		}
		lastchar++;
	}
	
	for(int i = 0; i < numLines; i++){
		
		printf("%s", array[i]);
	}
	
	for(int i = 0; i < numLines; i++){
		if(isEmpty(L)){
			append(L, i);
			
		} else {
			while(index(L) != -1){
				if(strcmp(array[get(L)], array[i]) < 0){
					moveNext(L);
				} else {
					break;
				}
			}
			if(index(L) == -1){
				moveBack(L);
				insertAfter(L, i);
				
			} else {
				insertBefore(L, i);
				
			}
		}
		moveFront(L);
	}
	//printfList(L);
	lastchar = 0;
	while (true)
	{
		if(array[back(L)][lastchar] == '\n'){
			array[back(L)][lastchar] = '\0';
			
			break;
		}
		lastchar++;
	}
	moveFront(L);
	
	rewind(out);
	//printList(out, L);
	printf("\n");
	while(index(L) != -1){
		//printf("test\n");
		fprintf(out, "%s", array[get(L)]);
		moveNext(L);
	}
	freeList(&L);
	fclose(in);
	fclose(out);
	for(int i = 0; i < numLines; i++){
		free(array[i]);
	}
	free(array);

	return 0;
}