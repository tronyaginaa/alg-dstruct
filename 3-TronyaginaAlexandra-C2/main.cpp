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
    graph = (int**)malloc(numOfVertices * sizeof(int*));
    feelGraph();
    if (!graph) {
        free(checkedVertices);
        exit(1);
    }
}

void memoryFree(void){
    free(checkedVertices);
    for (int i = 0; i < numOfVertices; i++) 
        free(graph[i]);
    free(graph);
}

 void readGraph(){
     int first, second; //Vertices incident to an edge
     fscanf(stdin, "%i", &numOfVertices);
     memoryInit();
     while (fscanf(stdin, "%i %i", &first, &second) != EOF) 
         graph[first][second] = graph[second][first] = TRUE;
     return;
 }

void DFS(int num, int** graph, int* checkedVertices, int numOfVertices){
    fprintf(stdout, "%i ", num);
    checkedVertices[num] = TRUE;
    for (int i = 0; i < numOfVertices; i++) 
        if (graph[num][i] && !checkedVertices[i])
            DFS(i, graph, checkedVertices, numOfVertices);
    return;
}

/*int main(void) {
    readGraph();
    DFS(0, graph, checkedVertices, numOfVertices);
    memoryFree();
    return 0;
}*/
