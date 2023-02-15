#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10

int main(int argc, char **argv){
	if(argc < 3){
		
		printf("Sparse Error: calling Sparse with too few arguements.\n");
		exit(EXIT_FAILURE);
	} else if(argc > 3){
		
		printf("Sparse Error: calling Sparse with too many arguements.\n");
		exit(EXIT_FAILURE);
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Sparse Error: input file not found.\n");
		exit(EXIT_FAILURE);
	}
	if(out == NULL){
		printf("Sparse Error: output file not found.\n");
		exit(EXIT_FAILURE);
	}
	int c, first, last;
	char* array = calloc((MAX_LINE_LENGTH), sizeof(char));
	fscanf(in, "%d %d %d", &c, &first, &last);
	fgets(array, 10, in);
	Matrix A = newMatrix(c);
	Matrix B = newMatrix(c);
	int row, column;
	double value;
	for(int i = 0; i < first; i++){
		fscanf(in, "%d %d %lf", &row, &column, &value);
		changeEntry(A, row, column, value);
	}
	fgets(array, 10, in);
	for(int i = 0; i < last; i++){
		fscanf(in, "%d %d %lf", &row, &column, &value);
		changeEntry(B, row, column, value);
	}
	fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
	printMatrix(out, A);
	fprintf(out, "\n");
	fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
	printMatrix(out, B);
	fprintf(out, "\n");
	Matrix C = scalarMult(1.5, A);
	fprintf(out, "(1.5)*A =\n");
	printMatrix(out, C);
	fprintf(out, "\n");
	Matrix D = sum(A, B);
	fprintf(out, "A+B =\n");
	printMatrix(out, D);
	fprintf(out, "\n");
	Matrix E = sum(A, A);
	fprintf(out, "A+A =\n");
	printMatrix(out, E);
	fprintf(out, "\n");
	Matrix F = diff(B, A);
	fprintf(out, "B-A =\n");
	printMatrix(out, F);
	fprintf(out, "\n");
	Matrix G = diff(A, A);
	fprintf(out, "A-A =\n");
	printMatrix(out, G);
	fprintf(out, "\n");
	Matrix H = transpose(A);
	fprintf(out, "Transpose(A) =\n");
	printMatrix(out, H);
	fprintf(out, "\n");
	Matrix I = product(A, B);
	fprintf(out, "A*B =\n");
	printMatrix(out, I);
	fprintf(out, "\n");
	Matrix J = product(B, B);
	fprintf(out, "B*B =\n");
	printMatrix(out, J);
	fprintf(out, "\n");
	fclose(in);
	fclose(out);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);
	freeMatrix(&I);
	freeMatrix(&J);
	free(array);
	return 1;
}