//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node before;

} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->before = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   assert( L!=NULL );
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;

   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}



// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)

ListElement getFront(List L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling getFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// length()
// Returns the length of L.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns the index of L.
int index(List L){
	if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   return(L->index);
}

// front()
// Returns the front element of L.
// Pre: length() > 0
int front(List L){
	if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling back() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);   
}

// back()
// Returns the back element of L.
// Pre: length() > 0
int back(List L){
	if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling back() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);   
}

// get()
// Returns the cursor element of L.
// Pre: length() > 0
int get(List L){
	if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling get() on empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);   
}

// equals()
// Returns true if A is in the same state as B, false otherwise.
bool equals(List A, List B){
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   

   bool eq;
   Node N, M;

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
   }
   return eq;
}


// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length == 0);
}


// Manipulation procedures ----------------------------------------------------


// clear()
// Resets L to its original empty state.
void clear(List L){
	if(L!=NULL) { 
      while( !isEmpty(L) ) { 
         deleteFront(L); 
    }
    L->cursor = L->back = L->front = NULL;
	L->index = -1;
	L->length = 0;  
      
   }
}

// set()
// Overwrites selected element's data with x
// Pre: length() > 0, index() >= 0
void set(List L, int x){
	if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling set() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) < 0) {
	printf("List Error: calling set() with no element selected\n");
    exit(EXIT_FAILURE);
   }
   L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L){
	if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling moveFront() on empty List\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->front;
   L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L){
	if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->back;
   L->index = length(L) - 1;
}

// movePrev()
// If the cursor is defined and not at the front, move the cursor one step towards the front
// If the cursor is defined at the front, it becomes undefined
// If the cursor is undefined do nothing
void movePrev(List L){
	if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling movePrev() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (L->cursor == NULL){
	 return;
   } else if(index(L) == 0){
	L->cursor = NULL;
	L->index = -1;
	return;
   }
   L->cursor = L->cursor->before;
   L->index--;
}

// moveNext()
// If the cursor is defined and not at the back, move the cursor one step towards the back
// If the cursor is defined at the back, it becomes undefined
// If the cursor is undefined do nothing
void moveNext(List L){
	if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling moveNext() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (L->cursor == NULL){
	 return;
   } else if(index(L) == length(L)-1){
	   L->cursor = NULL;
	   L->index = -1;
	   return;
   }
   L->cursor = L->cursor->next;
   L->index++;
}

// prepend()
// Insert new element into L.
// If L is non-empty the element goes before the front element.
void prepend(List L, int x){
   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   if(length(L) == 0){
      Node N = newNode(x);
      L->front = N;
      L->back = N;      
      
   } else {
      Node N = newNode(x);
      L->front->before = N;
      N->next = L->front;
      L->front = N;
      if(index(L) != -1){
         L->index++;
      }
   }
   L->length++;
}

// append()
// Insert new element into L.
// If L is non-empty the element goes after the back element.
void append(List L, int x){
   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   if(length(L) == 0){
      Node N = newNode(x);
      L->front = N;
      L->back = N;      
      
   } else {
      Node N = newNode(x);
      L->back->next = N;
      N->before = L->back;
      L->back = N;
     
   }
   L->length++;
}

// insertBefore()
// Inserts an element before the cursor.
// Pre: length() > 0, index()>=0
void insertBefore(List L, int x){
	if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	   printf("List Error: calling insertBefore() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) == -1) {
	 printf("List Error: calling insertBefore() with no element selected\n");
    exit(EXIT_FAILURE);
   }
   
   if(L->cursor->before != NULL){
      Node N = newNode(x);
      L->cursor->before->next = N;
      N->before = L->cursor->before;
      L->cursor->before = N;
      
      N->next = L->cursor;
      L->length++;
      L->index += 1;
   } else {
      prepend(L, x);
      
   }
   
   
}

// insertAfter()
// Inserts an element after the cursor.
// Pre: length() > 0, index()>=0
void insertAfter(List L, int x){
	if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling insertAfter() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) < 0) {
	printf("List Error: calling insertAfter() with no element selected\n");
    exit(EXIT_FAILURE);
   }
   
   if(L->cursor->next != NULL){
      Node N = newNode(x);
      L->cursor->next->before = N;
      N->next = L->cursor->next;
      
      
      L->cursor->next = N;
      N->before = L->cursor;
       L->length++;
      
   } else {
      append(L, x);
      
   }
   
   
  
}

// deleteFront()
// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L){
	if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling deleteFront() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) == 0){
	   delete(L);
	   return;
   }
   
   
   Node N = NULL;
   N = L->front;
   if( length(L)>1 ) { 
	   L->front->next->before = NULL;
      L->front = L->front->next; 
      if(L->index != -1){
         L->index -= 1;
      }
   }else{ 
      L->front = L->back = NULL; 
   }
   
   L->length--;
   freeNode(&N);
}

// deleteBack()
// Deletes the Back element.
// Pre: length() > 0
void deleteBack(List L){
	if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	  printf("List Error: calling deleteBack() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) == length(L) - 1){
	  delete(L);
	  return;
   }
   
   
   Node N = NULL;
   N = L->back;
   if( length(L)>1 ) { 
      L->back->before->next = NULL;
	  L->back = L->back->before;
   }else{ 
      L->front = L->back = NULL; 
   }
   L->length--;
   freeNode(&N);
}

// delete()
// Deletes the selected element and makes the cursor undefined.
// Pre: length() > 0, index()>=0
void delete(List L){
	if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } else if (L->length <= 0) {
	   printf("List Error: calling delete() on empty List\n");
      exit(EXIT_FAILURE);
   } else if (index(L) < 0) {
	   printf("List Error: calling delete() with no element selected\n");
      exit(EXIT_FAILURE);
   }
   Node N = NULL;
   N = L->cursor;

   if( length(L)>1 ) { 
		if(index(L) == 0){
			L->front->next->before = NULL;
			L->front = L->front->next;
			
		}else if (index(L) == length(L) - 1){
			L->back->before->next = NULL;
			L->back = L->back->before;
		}else {
			N->next->before = N->before;
			N->before->next = N->next;
		} 
   }else{ 
      L->front = L->back = NULL; 
   }
    L->index = -1;
	 L->cursor = NULL;
    L->length--;
    freeNode(&N);
}

// EnList()
// Places new data at the back of L.
void EnList(List L, ListElement data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling EnList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   
   if( isEmpty(L) ) { 
      L->front = L->back = N; 
   }else{ 
      L->back->next = N; 
      L->back = N; 
   }
   L->length++;
}

// DeList()
// Deletes data at front of L.
// Pre: !isEmpty(L)
void Delist(List L){
   Node N = NULL;

   
   if( isEmpty(L) ){
      printf("List Error: calling Delist() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   
   if( length(L)>1 ) { 
      L->front = L->front->next; 
      L->front->before = NULL;
   }else{ 
      L->front = L->back = NULL; 
   }
   L->length--;
   freeNode(&N);
}


// Other Functions ------------------------------------------------------------

// printfList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.
void printfList(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printfList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   for(N = L->front; N != NULL; N = N->next){
      printf(FORMAT" ", N->data);
   }
   printf("\n");
}

// printList()
// Prints a string representation of L to the file pointed to be out.
// The string representation is a space sepereated sequence of integers with front on the left.
void printList(FILE* out, List L){
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   for(int i = 0; i < length(L); i++){
      fprintf(out, "%d ", N->data);
      N = N->next;
   }
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined.
// The state of L in unchanged.
List copyList(List L){
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
   List R = newList();
   for(int i = 0; i < length(L); i++){
      append(R, N->data);
      N = N->next;
   }
   return R;
}


// concatList()
// Returns a new List which is a concatenation of A and B
// The cursor in the new list is undefined
// The states of A and B remain unchanged
List concatList(List A, List B){
   List L = newList();
   for(int i = 0; i < A->length; i++){
      append(L, A->front->data);
   }
   return L;
}

