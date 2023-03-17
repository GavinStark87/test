//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"


// structs --------------------------------------------------------------------

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
   int column;
   double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj{
   List* Entries;
   int size;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	M->Entries = (List *)calloc(n + 1, sizeof(List));
	for(int i = 1; i < n + 1; i++){
		M->Entries[i] = newList();
	}
	M->size = n;
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		if((*pM)->Entries!=NULL){
			for(int i = 0; i < (*pM)->size + 1; i++){
				if((*pM)->Entries[i] != NULL && !isEmpty((*pM)->Entries[i])){
					moveFront((*pM)->Entries[i]);
					while(index((*pM)->Entries[i]) != -1){
						free((Entry)get((*pM)->Entries[i]));
						moveNext((*pM)->Entries[i]);
					}
				}
				freeList(&((*pM)->Entries[i]));
			}
			free((*pM)->Entries);
			(*pM)->Entries = NULL;
		}
	}
	free(*pM);
	*pM = NULL;
}

// newEntry()
// Creates a new entry with column x and value y
Entry newEntry(int x, double y){
	Entry E;
	E = malloc(sizeof(EntryObj));
	E->column = x;
	E->value = y;
	return E;
}



// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if( M==NULL ){
      printf("Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if( M==NULL ){
      printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	printf("entering NNZ\n");
	int ret = 0;
	for(int i = 1; i < size(M) + 1; i++){
		if(!isEmpty(M->Entries[i])){
			ret += length(M->Entries[i]);
		}
	}
	return ret;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	if(size(A) != size(B)){
		printf("returning false size\n");
		return 0;
	}
	for(int i = 1; i < size(A) + 1; i++){
		if(length(A->Entries[i]) != length(B->Entries[i])){
			printf("returning false list length list %d\n", i);
			return 0;
		} else if (!isEmpty(A->Entries[i])){
			moveFront(A->Entries[i]);
			moveFront(B->Entries[i]);
			while(index(A->Entries[i]) != -1){
				if((((Entry)get(A->Entries[i]))->column != ((Entry)get(B->Entries[i]))->column) || ((Entry)get(A->Entries[i]))->value != ((Entry)get(B->Entries[i]))->value){
					printf("returning false column/val %d %d %d %f %f\n", (((Entry)get(A->Entries[i]))->column != ((Entry)get(B->Entries[i]))->column), ((Entry)get(A->Entries[i]))->value != ((Entry)get(B->Entries[i]))->value, i, ((Entry)get(A->Entries[i]))->value, ((Entry)get(B->Entries[i]))->value);
					return 0;
				}
				moveNext(A->Entries[i]);
				moveNext(B->Entries[i]);
			}
		}
	}
	printf("returning true\n");
	return 1;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if( M==NULL ){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	for(int i = 1; i < M->size + 1; i++){
		clear(M->Entries[i]);
	}
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if( M==NULL ){
      printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    } else if((!(1 <= i) || !(i <= (M)->size)) || (!(1 <= j) || !(j <= (M)->size))){
	  printf("Matrix Error: calling changeEntry() on with out of range index\n");
      exit(EXIT_FAILURE);
	}
	
	if(isEmpty(M->Entries[i])){
		if(x == 0){
			return;
		}
		Entry E = newEntry(j, x);
		append(M->Entries[i], E);
	} else {
		moveFront(M->Entries[i]);
		while(index(M->Entries[i]) != -1 && ((Entry)get(M->Entries[i]))->column <= j){
			if(((Entry)get(M->Entries[i]))->column == j){
				free((Entry)get(M->Entries[i]));
				if(x == 0){
					delete(M->Entries[i]);
					return;
				}
				Entry E = newEntry(j, x);
				set(M->Entries[i], E);
				return;
			}
			moveNext(M->Entries[i]);
		}
		if(index(M->Entries[i]) == -1){
			if(x == 0){
				return;
			}
			Entry E = newEntry(j, x);
			append(M->Entries[i], E);
		} else {
			if(x == 0){
				return;
			}
			Entry E = newEntry(j, x);
			insertBefore(M->Entries[i], E);
		}

	}
}

// Matrix Arithmetic operations-----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if( A==NULL ){
      printf("Matrix Error: calling copy() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i++){
		if(!isEmpty(A->Entries[i])){
			moveFront(A->Entries[i]);
			while(index(A->Entries[i]) != -1){
				changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
				moveNext(A->Entries[i]);
			}
		}
	}
	return M;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if( A==NULL ){
      printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i++){
		if(!isEmpty(A->Entries[i])){
			moveFront(A->Entries[i]);
			while(index(A->Entries[i]) != -1){
				changeEntry(M, ((Entry)get(A->Entries[i]))->column, i, ((Entry)get(A->Entries[i]))->value);
				moveNext(A->Entries[i]);
			}
		}
	}
	return M;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if( A==NULL ){
      printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i++){
		if(!isEmpty(A->Entries[i])){
			moveFront(A->Entries[i]);
			while(index(A->Entries[i]) != -1){
				changeEntry(M, i,  ((Entry)get(A->Entries[i]))->column, x * ((Entry)get(A->Entries[i]))->value);
				moveNext(A->Entries[i]);
			}
		}
	}
	return M;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
      printf("Matrix Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
		printf("Matrix Error: calling sum() matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	if(equals(A, B)){
		for(int i = 1; i < size(A) + 1; i++){
			if(!isEmpty(A->Entries[i])){
				moveFront(A->Entries[i]);
				while(index(A->Entries[i]) != -1){
					changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value + ((Entry)get(A->Entries[i]))->value);
					moveNext(A->Entries[i]);
				}
			}
		}
	} else {
		for(int i = 1; i < size(A) + 1; i++){
			if(!isEmpty(A->Entries[i]) && !isEmpty(B->Entries[i])){
				moveFront(A->Entries[i]);
				moveFront(B->Entries[i]);
				while(index(A->Entries[i]) != -1 || index(B->Entries[i]) != -1){
					if(index(A->Entries[i]) == -1){
						changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, ((Entry)get(B->Entries[i]))->value);
						moveNext(B->Entries[i]);
					} else if(index(B->Entries[i]) == -1){
						changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
						moveNext(A->Entries[i]);
					} else if(((Entry)get(A->Entries[i]))->column == ((Entry)get(B->Entries[i]))->column){
						changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value + ((Entry)get(B->Entries[i]))->value);
						printf("%d %d\n", ((Entry)get(A->Entries[i]))->column,((Entry)get(B->Entries[i]))->column);
						moveNext(A->Entries[i]);
						moveNext(B->Entries[i]);
					} else if(((Entry)get(A->Entries[i]))->column < ((Entry)get(B->Entries[i]))->column){
						changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
						moveNext(A->Entries[i]);
					} else if(((Entry)get(B->Entries[i]))->column < ((Entry)get(A->Entries[i]))->column){
						changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, ((Entry)get(B->Entries[i]))->value);
						moveNext(B->Entries[i]);
					}
				}
			} else if(isEmpty(A->Entries[i]) && !isEmpty(B->Entries[i])){
				moveFront(B->Entries[i]);
				while(index(B->Entries[i]) != -1){
					changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, ((Entry)get(B->Entries[i]))->value);
					moveNext(B->Entries[i]);
				}
			} else if(!isEmpty(A->Entries[i]) && isEmpty(B->Entries	[i])){
				moveFront(A->Entries[i]);
				while(index(A->Entries[i]) != -1){
					changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
					moveNext(A->Entries[i]);
				}
			}
		}
	}
	return M;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
      printf("Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
		printf("Matrix Error: calling diff() matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	if(equals(A, B)){
		return M;
	}
	for(int i = 1; i < size(A) + 1; i++){
		if(!isEmpty(A->Entries[i]) && !isEmpty(B->Entries[i])){
			moveFront(A->Entries[i]);
			moveFront(B->Entries[i]);
			while(index(A->Entries[i]) != -1 || index(B->Entries[i]) != -1){
				if(index(A->Entries[i]) == -1 && !isEmpty(B->Entries[i])){
					changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, -1 * ((Entry)get(B->Entries[i]))->value);
					moveNext(B->Entries[i]);
				} else if(index(B->Entries[i]) == -1){
					changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
					moveNext(A->Entries[i]);
				} else if(((Entry)get(A->Entries[i]))->column == ((Entry)get(B->Entries[i]))->column){
					changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value - ((Entry)get(B->Entries[i]))->value);
					moveNext(A->Entries[i]);
					moveNext(B->Entries[i]);
				} else if(((Entry)get(A->Entries[i]))->column < ((Entry)get(B->Entries[i]))->column){
					changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
					moveNext(A->Entries[i]);
				} else if(((Entry)get(B->Entries[i]))->column < ((Entry)get(A->Entries[i]))->column){
					changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, -1 * ((Entry)get(B->Entries[i]))->value);
					moveNext(B->Entries[i]);
				}
			}
		} else if(isEmpty(A->Entries[i]) && !isEmpty(B->Entries[i])){
			moveFront(B->Entries[i]);
			while(index(B->Entries[i]) != -1){
				changeEntry(M, i, ((Entry)get(B->Entries[i]))->column, -1 * ((Entry)get(B->Entries[i]))->value);
				moveNext(B->Entries[i]);
			}
		} else if(!isEmpty(A->Entries[i]) && isEmpty(B->Entries	[i])){
			moveFront(A->Entries[i]);
			while(index(A->Entries[i]) != -1){
				changeEntry(M, i, ((Entry)get(A->Entries[i]))->column, ((Entry)get(A->Entries[i]))->value);
				moveNext(A->Entries[i]);
			}
		}
	}
	return M;
}

// vectorDot()
// Returns the dot product of the two lists
double vectorDot(List P, List Q){
	if(P==NULL || Q==NULL){
      printf("Matrix Error: calling vectorDor() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
	double ret = 0;
	if(!isEmpty(P) && !isEmpty(Q)){
		moveFront(P);
		moveFront(Q);
		while(index(P) != -1 && index(Q) != -1){
			if(((Entry)get(P))->column == ((Entry)get(Q))->column){
				ret += ((Entry)get(P))->value * ((Entry)get(Q))->value;
				moveNext(P);
				moveNext(Q);
			} else if(((Entry)get(P))->column < ((Entry)get(Q))->column){
				moveNext(P);
			} else if(((Entry)get(P))->column > ((Entry)get(Q))->column){
				moveNext(Q);
			}
		}
	}
	return ret;
}



// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
      printf("Matrix Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    } else if(size(A) != size(B)){
		printf("Matrix Error: calling diff() matrices of different sizes\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	Matrix Bt = transpose(B);
	for(int i = 1; i < size(A) + 1; i++){
		if(!isEmpty(A->Entries[i])){
			for(int j = 1; j < size(A) + 1; j++){
				if(!isEmpty(Bt->Entries[j])){
					changeEntry(M, i, j, vectorDot(A->Entries[i], Bt->Entries[j]));
				}
			}
		}
	}
	freeMatrix(&Bt);
	return M;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if( M==NULL ){
      printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
	for(int i = 1; i < M->size + 1; i++){
		if(!isEmpty(M->Entries[i])){
			fprintf(out, "%d:", i);
			moveFront(M->Entries[i]);
			while(index(M->Entries[i]) != -1){
				fprintf(out, " (%d, %.1f)", ((Entry)get(M->Entries[i]))->column, ((Entry)get(M->Entries[i]))->value);
				moveNext(M->Entries[i]);
			}
			fprintf(out, "\n");
		}
		
	}
}












