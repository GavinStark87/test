#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"


// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj{
	List* neighbors;
	int* color;
	int* parent;
	int* distance;
	int order;
	int size;
	int source;

} GraphObj;

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a reference to a new Graph object with n vertices and no edges
Graph newGraph(int n){
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->neighbors = (List *)calloc(n + 1, sizeof(List));
	G->color = (int *)calloc(n + 1, sizeof(int));
	G->parent = (int *)calloc(n + 1, sizeof(int));
	G->distance = (int *)calloc(n + 1, sizeof(int));
	for(int i = 1; i < n + 1; i++){//may cause issue
		G->neighbors[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	
	
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}


// freeGraph()
// Frees all heap memory associated with Graph *pG, and set *pG to NULL.
void freeGraph(Graph* pG){
	if(pG!=NULL && *pG!=NULL){
		if((*pG)->neighbors!=NULL){
			for(int i = 0; i < (*pG)->order + 1; i++){
				freeList(&((*pG)->neighbors[i]));
			}
			free((*pG)->neighbors);
			(*pG)->neighbors = NULL;
		}
		
		if((*pG)->color!=NULL){
			free(((*pG)->color));
			(*pG)->color = NULL;
		}
		if((*pG)->parent!=NULL){
			free((*pG)->parent);
			(*pG)->parent = NULL;
		}
		if((*pG)->distance!=NULL){
			free((*pG)->distance);
			(*pG)->distance = NULL;
		}
		free(*pG);
		*pG = NULL;

	}
}

// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of the graph.
int getOrder(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->order;
}

// getSize()
// Returns the size of the graph.
int getSize(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->size;
}

// getSource()
// Returns the source vertex most recently used in BFS() or NIL if BFS() has not yet been called.
int getSource(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return G->source;
}

// getParent()
// Returns the parent vertex of u in the BFS tree created by BFS and NIL if BFS has not been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G))){
	  printf("Graph Error: calling getParent() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   if(getSource(G)==NIL){
	 return NIL;
   } else {
	 return G->parent[u];
   }
}

// getDistance()
// Returns the distance between u and the most recent BFS source vertex or INF if BFS has not been called.
// Pre: 1 <= u <= getOrder(G) 
int getDist(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getDistance() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G))){
	  printf("Graph Error: calling getDistance() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   if(getSource(G)==NIL){
	 return INF;
   } else {
	 return G->distance[u];
   }
}

// getColor()
// Returns the color of vertex u.
// Pre: 1 <= u <= getOrder(G) 
int getColor(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getColor() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G))){
	  printf("Graph Error: calling getColor() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->color[u];
}

// getNeighbors()
// Returns the list of neighbors for vertex u.
// Pre: 1 <= u <= getOrder(G) 
List getNeighbors(Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getNeighbors() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G))){
	  printf("Graph Error: calling getNeighbors() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   return G->neighbors[u];
}

// getPath()
// Appends to L the vertices of the shortest path between source and u if such a path exists. If no such path exists NIL is appended to L instead.
// Pre: 1 <= u <= getOrder(G) and getSource(G) != NIL
void getPath(List L, Graph G, int u){
	if( G==NULL ){
      printf("Graph Error: calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G))){
	  printf("Graph Error: calling getPath() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   } else if (getSource(G) == NIL){
	  printf("Graph Error: calling getPath() with no source vertex\n");
      exit(EXIT_FAILURE);
   }
   if(u == getSource(G)){
	  append(L, getSource(G));
   } else if(G->parent[u] == NIL){
	  append(L, NIL);
   } else {
	  getPath(L, G, G->parent[u]);
	  append(L, u);
   }
}

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G
void makeNull(Graph G){
	if( G==NULL ){
      printf("Graph Error: calling makeNull() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i < G->order + 1; i++){
		clear(G->neighbors[i]);
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
   }
   G->source = NIL;
   G->size = 0;
}

// addEdge()
// Adds a new edge joining u to v.
// Pre: 1 <= u <= getOrder(G) and 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
	if( G==NULL ){
      printf("Graph Error: calling addEdge() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G)) || !(1 <= v) || !(v <= getOrder(G))){
	  printf("Graph Error: calling addEdge() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(G->neighbors[u])){
	  append(G->neighbors[u], v);
   } else {
	  moveFront(G->neighbors[u]);
	  while(index(G->neighbors[u]) != -1 && get(G->neighbors[u]) < v){
			if(get(G->neighbors[u]) == v){
				return;
			}
			moveNext(G->neighbors[u]);
	  }
	  if(index(G->neighbors[u]) == -1){
			moveBack(G->neighbors[u]);
			insertAfter(G->neighbors[u], v);
	} else {
			insertBefore(G->neighbors[u], v);
				
		}
   }
   if(isEmpty(G->neighbors[v])){
	  append(G->neighbors[v], u);
   } else {
	  moveFront(G->neighbors[v]);
	  while(index(G->neighbors[v]) != -1 && get(G->neighbors[v]) < u){
			if(get(G->neighbors[v]) == u){
				return;
			}
			moveNext(G->neighbors[v]);
	  }
	  if(index(G->neighbors[v]) == -1){
			moveBack(G->neighbors[v]);
			insertAfter(G->neighbors[v], u);
	} else {
			insertBefore(G->neighbors[v], u);
				
		}
   }
   G->size += 1;
  
}

// addArc()
// Adds a new directed edge joining u to v.
// Pre: 1 <= u <= getOrder(G) and 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v){
	if( G==NULL ){
      printf("Graph Error: calling addArc() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if (!(1 <= u) || !(u <= getOrder(G)) || !(1 <= v) || !(v <= getOrder(G))){
	  printf("Graph Error: calling addArc() on an inelligable vertex\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(G->neighbors[u])){
	  append(G->neighbors[u], v);
   } else {
	  moveFront(G->neighbors[u]);
	  while(index(G->neighbors[u]) != -1 && get(G->neighbors[u]) < v){
			if(get(G->neighbors[u]) == v){
				return;
			}
			moveNext(G->neighbors[u]);
	  }
	  if(index(G->neighbors[u]) == -1){
			moveBack(G->neighbors[u]);
			insertAfter(G->neighbors[u], v);
	} else {
			insertBefore(G->neighbors[u], v);
				
		}
   }
   
	G->size += 1;
}

// BFS()
// Runs the BFS alglrithm on graph G with source s and sets the parent, distance, color, and source fields of G accodingly
void BFS(Graph G, int s){
	if( G==NULL ){
      printf("Graph Error: calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   } else if(s > G->order || s < 1){
	  printf("Graph Error: calling BFS() with out of range source\n");
      exit(EXIT_FAILURE);
   }
   G->source = s;
	for(int i = 1; i < G->order + 1; i++){
		if(i != s){
			G->color[i] = 1;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		} else {
			G->color[s] = 2;
			G->distance[s] = 0;
			G->parent[s] = NIL;
		}
	}
	List Q = newList();
	append(Q, s);
	while(!isEmpty(Q)){
		int x = front(Q);
		deleteFront(Q);
		if(!isEmpty(G->neighbors[x])){
			moveFront(G->neighbors[x]);
			while(index(G->neighbors[x]) != -1 && !isEmpty(G->neighbors[x])){
				if(G->color[get(G->neighbors[x])] == 1){
					G->color[get(G->neighbors[x])] = 2;
					G->distance[get(G->neighbors[x])] = G->distance[x] + 1;
					G->parent[get(G->neighbors[x])] = x;
					append(Q, get(G->neighbors[x]));
				}
				moveNext(G->neighbors[x]);
			}
		
		}
		G->color[x] = 3;
	}
	free(Q);
}

// printPath()
// Prints the adjacency list of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
	if( G==NULL ){
      printf("Graph Error: calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i < G->order + 1; i++){
		fprintf(out, "%d:", i);
		if((G->neighbors[i] != NULL) && !isEmpty(G->neighbors[i])){
			moveFront(G->neighbors[i]);
		}
		
		while((G->neighbors[i] != NULL) && !isEmpty(G->neighbors[i]) && index(G->neighbors[i]) != -1){
			
			fprintf(out, " %d", get(G->neighbors[i]));
			moveNext(G->neighbors[i]);
		}
		fprintf(out, "\n");
   }
}

