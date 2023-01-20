/*
Gavin Stark
gestark
pa1
*/
//-----------------------------------------------------------------------------
// ListTest.c
// Another test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

  
   
   List R = newList();
   FILE* out;
   out = fopen("out.txt", "w");
   printf("\n");
   append(R, 3);
   moveFront(R);
   insertBefore(R, 5);
   insertAfter(R, 7);
   printf("%d\n", get(R));
   moveNext(R);
   printf("%d\n", get(R));
   prepend(R, 11);
   moveFront(R);
   printf("%d %d\n", get(R), index(R));
   moveBack(R);
   printf("%d %d %d\n", get(R), index(R), length(R));
   
   movePrev(R);
   printf("%d %d\n", get(R), index(R));
   set(R, 7);
   printf("%d %d %d\n", get(R), index(R), length(R));
   moveNext(R);
   printfList(R);
   deleteFront(R);
   deleteBack(R);
   printfList(R);
   clear(R);
   printfList(R);
   List Q = copyList(R);
   printList(out, Q);
   
   fclose(out);

  
   freeList(&Q);
   freeList(&R);
   return(EXIT_SUCCESS);
}
