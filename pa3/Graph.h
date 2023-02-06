#include<stdbool.h>
#include<stdio.h>
#include "List.h"


#ifndef GRAPH_H_INCLUDE_
#define UNDEF -1
#define NIL 0



// Exported types -------------------------------------------------------------

// typedef struct GraphObj GraphObj;

typedef struct GraphObj* Graph;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns a reference to a new Graph object with n vertices and no edges
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with Graph *pG, and set *pG to NULL.
void freeGraph(Graph* pG);

// transpose()
// Returns a new graph object representing the transpose of G.
Graph transpose(Graph G);

// copyGraph()
// Returns a new graph that is a copy of G
Graph copyGraph(Graph G);

// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of the graph.
int getOrder(Graph G);

// getSize()
// Returns the size of the graph.
int getSize(Graph G);

// getSource()
// Returns the source vertex most recently used in BFS() or NIL if BFS() has not yet been called.
int getSource(Graph G);

// getParent()
// Returns the parent vertex of u in the BFS tree created by BFS and NIL if BFS has not been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of u if DFS has been called and UNDEF if it has not been called.
// Pre: 1 <= u <= getOrder(G) 
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of u if DFS has been called and UNDEF if it has not been called.
// Pre: 1 <= u <= getOrder(G) 
int getFinish(Graph G, int u);

// getColor()
// Returns the color of vertex u.
// Pre: 1 <= u <= getOrder(G) 
int getColor(Graph G, int u);

// getNeighbors()
// Returns the list of neighbors for vertex u.
// Pre: 1 <= u <= getOrder(G) 
List getNeighbors(Graph G, int u);

// getPath()
// Appends to L the vertices of the shortest path between source and u if such a path exists. If no such path exists NIL is appended to L instead.
// Pre: 1 <= u <= getOrder(G) 
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------

// makeNull()
// Deletes all edges of G
void makeNull(Graph G);

// addEdge()
// Adds a new edge joining u to v.
// Pre: 1 <= u <= getOrder(G) and 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Adds a new directed edge joining u to v.
// Pre: 1 <= u <= getOrder(G) and 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// Runs the BFS alglrithm on graph G with source s and sets the parent, distance, color, and source fields of G accodingly
void BFS(Graph G, int s);

// DFS()
// Runs the DFS algorithm on graph G in the order of S and then stores the vertices in order of finish time in S.
// Pre: length(S) == getOrder(G) and S contains some permutation of the vertices of G
void DFS(Graph G, List S);

// Other Functions ------------------------------------------------------------

// printPath()
// Prints the adjacency list of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);

#endif
