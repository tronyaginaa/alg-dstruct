//
//  main.cpp
//  3-TronyaginaAlexandra-C2
//
//  Created by Alexandra Tronyagina on 12.11.2021.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "3-TronyaginaAlexandra-C2/LabCHeader.h"

int* checkedVertices;
int** graph;
int numOfVertices;
myStack_t* stack;

void push(myStack_t** stack, int value) {
    node_t* tmp = (node_t*)malloc(sizeof(node_t));
    if (!tmp)
        exit(1);
    tmp->value = value;
    tmp->nextNode = (*stack)->head;
    (*stack)->head = tmp;
    return;
}

int pop(myStack_t** stack) {
    node_t* node;
    int value;
    node = (*stack)->head;
    (*stack)->head = node->nextNode;
    value = node->value;
    free(node);
    return value;
}

void fillGraph() {
    if (!graph)
        return;
    for (int i = 0; i < numOfVertices; i++) {
        graph[i] = (int*)malloc(numOfVertices * sizeof(int));
        if (!graph[i]) { //check if memory has been allocated and clear all memory allocated earlier
            for (int j = 0; j < i; j++)
                free(graph[j]);
            free(graph);
            free(stack);
            free(checkedVertices);
            exit(1);
        }
        checkedVertices[i] = FALSE;
        for (int j = 0; j < numOfVertices; j++)
            graph[i][j] = FALSE;
    }
    return;
}

void memoryInit() {
    stack = (myStack_t*)malloc(sizeof(myStack_t));
    stack->head = NULL;
    checkedVertices = (int*)malloc(numOfVertices * sizeof(int));
    if (!checkedVertices) {
        free(stack);
        exit(1);
    }
    graph = (int**)malloc(numOfVertices * sizeof(int*));
    if (!graph) {
        free(checkedVertices);
        free(stack);
        exit(1);
    }
    fillGraph();
    return;
}

void memoryFree(void) {
    free(stack);
    free(checkedVertices);
    for (int i = 0; i < numOfVertices; i++)
        free(graph[i]);
    free(graph);
    return;
}

void readGraph() {
    int first, second; //Vertices incident to an edge
    fscanf(stdin, "%i", &numOfVertices);
    memoryInit();
    while (fscanf(stdin, "%i %i", &first, &second) != EOF)
        graph[first][second] = graph[second][first] = TRUE;
    return;
}

void DFS(int num, int** graph, int* checkedVertices, int numOfVertices, myStack_t* stack) {
    push(&stack, num);
    while (stack->head) {
        num = pop(&stack);
        if (!checkedVertices[num]) {
            fprintf(stdout, "%i ", num);
            checkedVertices[num] = TRUE;
            for (int i = numOfVertices; i >= 0; i--)
                if (graph[num][i] && !checkedVertices[i])
                    push(&stack, i);
        }
    }
    return;
}

int main(void) {
    readGraph();
    DFS(0, graph, checkedVertices, numOfVertices, stack);
    memoryFree();
    return 0;
}
