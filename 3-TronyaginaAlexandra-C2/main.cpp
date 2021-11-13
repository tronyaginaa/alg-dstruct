//
//  main.cpp
//  3-TronyaginaAlexandra-C2
//
//  Created by Alexandra Tronyagina on 12.11.2021.
//

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE (!TRUE)

typedef struct node_t{
    int value;
    struct node_t* nextNode;
} node_t;

typedef struct myStack_t{
    node_t* head;
} myStack_t;

int* checkedVertices;
int** graph;
int numOfVertices = 0;
myStack_t* stack;

void feelGraph(){
    if (!graph)
        return;
    for (int i = 0; i < numOfVertices; i++) {
        graph[i] = (int*)malloc(numOfVertices * sizeof(int));
        if (!graph[i]) { //check if memory has been allocated and clear all memory allocated earlier
            for (int j = 0; j < i; j++)
                free(graph[j]);
            free(graph);
            return;
        }
        for (int j = 0; j < numOfVertices; j++) {
            checkedVertices[i] = FALSE;
            graph[i][j] = FALSE;
        }
    }
}

void memoryInit(){
    checkedVertices = (int*)malloc(numOfVertices * sizeof(int));
    if (!checkedVertices)
        exit(1);
    stack = (myStack_t*)malloc(sizeof(myStack_t));
    stack->head = NULL;
    if (!stack) {
        free(checkedVertices);
        exit(1);
    }
    graph = (int**)malloc(numOfVertices * sizeof(int*));
    feelGraph();
    if (!graph) {
        free(checkedVertices);
        free(stack);
        exit(1);
    }
}

void memoryFree(void){
    while (stack->head) {
        node_t* node = (stack)->head;
        (stack)->head = node->nextNode;
        free(node);
    }
    free(stack);
    free(checkedVertices);
    for (int i = 0; i < numOfVertices; i++) {
        free(graph[i]);
    }
    free(graph);
}

void push(myStack_t** stack, int value){
    node_t* tmp = (node_t*)malloc(sizeof(node_t));
    if (!tmp) {
        memoryFree();
        exit(1);
    }
    tmp->value = value;
    tmp->nextNode = (*stack)->head;
    (*stack)->head = tmp;
    return;
}

int pop(myStack_t** stack){
    node_t* node;
    int value;
    node = (*stack)->head;
    (*stack)->head = node->nextNode;
    value = node->value;
    free(node);
    return value;
}

 void readGraph(void){
     int first, second; //Vertices incident to an edge
     fscanf(stdin, "%i", &numOfVertices);
     memoryInit();
     while (fscanf(stdin, "%i %i", &first, &second) != EOF) {
         graph[first][second] = graph[second][first] = TRUE;
     }
     return;
 }

void DFS(int num){
    fprintf(stdout, "%i ", num);
    checkedVertices[num] = TRUE;
    for (int i = numOfVertices - 1; i > -1; i--) {
        if (graph[num][i] && !checkedVertices[i])
            push(&stack, i);
    }
    while (stack->head) {
        num = pop(&stack);
        if (!checkedVertices[num])
            DFS(num);
    }
    return;
}

int main(void) {
    readGraph();
    DFS(0);
    memoryFree();
    return 0;
}
