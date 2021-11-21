
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	#pragma warning (disable:4996)
	#include <stdio.h>
	#include <stdlib.h>

	#define TRUE 1
	#define FALSE (!TRUE)

    typedef struct node_t {
        int value;
        struct node_t* nextNode;
    } node_t;

    typedef struct myStack_t {
        node_t* head;
    } myStack_t;

// stack functions
	int pop(myStack_t* stack);
	myStack_t* push(myStack_t* stack, int value);

	void fillGraph(int** graph, int numOfVertices);
	void readGraph(FILE* stream, int** graph);
	void DFS(int num, int** graph, int numOfVertices);
	

#ifdef __cplusplus
}
#endif
