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


myStack_t* push(myStack_t* stack, int value) {
	node_t* tmp = (node_t*)malloc(sizeof(node_t));
	if (!tmp)
		return NULL;
	tmp->value = value;
	tmp->nextNode = stack->head;
	stack->head = tmp;
	return stack;
}

int pop(myStack_t* stack) {
	node_t* node;
	int value;
	node = stack->head;
	stack->head = node->nextNode;
	value = node->value;
	free(node);
	return value;
}

void stackDestroy(myStack_t* stack) {
	node_t* node = stack->head;
	while (node) {
		node = node->nextNode;
		free(node);
	}
	free(stack);
	return;
}

void fillGraph(int** graph, int numOfVertices) {
	for (int i = 0; i < numOfVertices; i++) {
		graph[i] = (int*)malloc(numOfVertices * sizeof(int));
		if (!graph[i]) { //check if memory has been allocated and clear all memory allocated earlier
			for (int j = 0; j < i; j++)
				free(graph[j]);
			free(graph);
			exit(1);
		}
		for (int j = 0; j < numOfVertices; j++)
			graph[i][j] = FALSE;
	}
	return;
}

void readGraph(FILE* stream, int** graph) {
	int numOfVertices;
	int first, second; //Vertices incident to an edge
	fscanf(stream, "%i", &numOfVertices);
	graph = (int**)malloc(numOfVertices * sizeof(int*));
	if (!graph)
		exit(1);
	fillGraph(graph, numOfVertices);
	while (fscanf(stream, "%i %i", &first, &second) != EOF)
		graph[first][second] = graph[second][first] = TRUE;
	return;
}

void DFS(int num, int** graph, int numOfVertices) {
	myStack_t* stack = (myStack_t*)malloc(sizeof(myStack_t));
	if (!stack)
		return;
	stack->head = NULL;
	int* checkedVertices = (int*)malloc(numOfVertices * sizeof(int));
	if (!checkedVertices) {
		free(stack);
		return;
	}
	for (int i = 0; i < numOfVertices; i++)
		checkedVertices[i] = FALSE;
	myStack_t* tmpStack;
	tmpStack = push(stack, num);
	if (!tmpStack) {
		free(checkedVertices);
		stackDestroy(stack);
		return;
	}
	stack = tmpStack;
	fprintf(stdout, "%i ", num);
	while (stack->head) {
		num = stack->head->value;
		checkedVertices[num] = TRUE;
		for (int i = 0; i < numOfVertices; i++)
			if (graph[num][i] && !checkedVertices[i]) {
				checkedVertices[i] = TRUE;
				fprintf(stdout, "%i ", i);
				tmpStack = push(stack, num);
				if (!tmpStack) {
					free(checkedVertices);
					stackDestroy(stack);
					return;
				}
				stack = tmpStack;
				num = i;
				i = 0;
			}
		pop(stack);
	}
	free(checkedVertices);
	stackDestroy(stack);
	return;
}
