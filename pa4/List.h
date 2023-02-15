/*
Gavin Stark
gestark
pa4
*/
//-----------------------------------------------------------------------------List
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>
#include<stdio.h>


#define FORMAT "%p"  // format string for ListElement


// Exported types -------------------------------------------------------------
typedef void* ListElement;
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList();

// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// getFront()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
ListElement getFront(List L);

// length()
// Returns the length of L.
int length(List L);

// index()
// Returns the index of L.
int index(List L);


// front()
// Returns the front element of L.
// Pre: length() > 0
void* front(List L);


// back()
// Returns the back element of L.
// Pre: length() > 0
void* back(List L);

// get()
// Returns the cursor element of L.
// Pre: length() > 0
void* get(List L);

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);


// Manipulation procedures ----------------------------------------------------
// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites selected element's data with x
// Pre: length() > 0, index() >= 0
void set(List L, void* x);

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L);

// movePrev()
// If the cursor is defined and not at the front, move the cursor one step towards the front
// If the cursor is defined at the front, it becomes undefined
// If the cursor is undefined do nothing
void movePrev(List L);

// moveNext()
// If the cursor is defined and not at the back, move the cursor one step towards the back
// If the cursor is defined at the back, it becomes undefined
// If the cursor is undefined do nothing
void moveNext(List L);

// prepend()
// Insert new element into L.
// If L is non-empty the element goes before the front element.
void prepend(List L, void* x);

// append()
// Insert new element into L.
// If L is non-empty the element goes after the back element.
void append(List L, void* x);

// insertBefore()
// Inserts an element before the cursor.
// Pre: length() > 0, index()>=0
void insertBefore(List L, void* x);

// insertAfter()
// Inserts an element after the cursor.
// Pre: length() > 0, index()>=0
void insertAfter(List L, void* x);

// deleteFront()
// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// Deletes the Back element.
// Pre: length() > 0
void deleteBack(List L);

// delete()
// Deletes the selected element and makes the cursor undefined.
// Pre: length() > 0, index()>=0
void delete(List L);


// EnList()
// Places new data at the back of Q.
void EnList(List L, ListElement data);

// DeList()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
void Delist(List L);


// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to stdout.
void printfList(List L);



#endif
