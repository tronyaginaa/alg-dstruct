#include "pch.h"
#include "LabCHeader.h"
#include <time.h>

/*
    OS: OS: Windows 10 Home, Version 20H2, Build 19042.1348
    IDE: Visual Studio 2019 Community Edition
    CPU: Intel(R) Core(TM) i5-1038NG7 CPU 2.00GHz
    RAM: 16 GB 
 
    RESULTS:
    GRAPH TRAVERSAL TIME: 30421 ms
    USED MEMORY: 2.1 GB
*/

#define TEST_NUM_OF_VERTICES 25000

TEST(DFS_test, FillingFileForStressTest){
    srand(time(NULL));
    int** graphToFeelFile = (int**)malloc(TEST_NUM_OF_VERTICES * sizeof(int*));
    ASSERT_TRUE(graphToFeelFile);
    for (int i = 0; i < TEST_NUM_OF_VERTICES; i++) {
        graphToFeelFile[i] = (int*)malloc(TEST_NUM_OF_VERTICES * sizeof(int));
        if (!graphToFeelFile[i]) {
            for (int j = 0; j < i; j++)
                free(graphToFeelFile[j]);
            free(graphToFeelFile);
            ASSERT_TRUE(!graphToFeelFile);
        }
    }
    for (int i = 0; i < TEST_NUM_OF_VERTICES; i++) 
        for (int j = i + 1; j < TEST_NUM_OF_VERTICES; j++)
            graphToFeelFile[i][j] = graphToFeelFile[j][i] = rand() % 2;
    FILE* f = fopen("graph_test.txt", "w");
    if (f == NULL) {
        for (int i = 0; i < TEST_NUM_OF_VERTICES; i++)
            for (int j = 0; j < TEST_NUM_OF_VERTICES; j++)
                free(graphToFeelFile[j]);
        free(graphToFeelFile);
        ASSERT_TRUE(f);
    }
    fprintf(f, "%i\n", TEST_NUM_OF_VERTICES);
    for (int i = 0; i < TEST_NUM_OF_VERTICES; i++)
        for (int j = i + 1; j < TEST_NUM_OF_VERTICES; j++)
            if (graphToFeelFile[i][j] == TRUE)
                fprintf(f, "%i %i\n", i, j);
    fclose(f);
    for (int i = 0; i < TEST_NUM_OF_VERTICES; i++)
        free(graphToFeelFile[i]);
    free(graphToFeelFile);
}

TEST(DFS_test, StressTest){
    int first, second, numOfVertices;
    FILE*f = fopen("graph_test.txt", "r");
    ASSERT_TRUE(f);
    fscanf(f, "%i", &numOfVertices);
    int* checkedVertices = (int*)malloc(numOfVertices * sizeof(int));
    if (!checkedVertices) {
        fclose(f);
        ASSERT_TRUE(checkedVertices);
    }
    myStack* stack = (myStack*)malloc(myStack);
    if (!stack) {
        free(checkedVertices);
        fclose(f);
        ASSERT_TRUE(stack);
    }
    stack->head = NULL;
    int** graph = (int**)malloc(numOfVertices * sizeof(int*));
    if(!graph) {
        free(checkedVertices);
        free(stack);
        fclose(f);
        ASSERT_TRUE(graph);
    }
    for (int i = 0; i < numOfVertices; i++) {
        graph[i] = (int*)malloc(numOfVertices * sizeof(int));
        if (!graph[i]) { 
            for (int j = 0; j < i; j++)
                free(graph[j]);
            free(graph);
            free(checkedVertices);
            free(stack);
            fclose(f);
            ASSERT_TRUE(!graph);
            }
        checkedVertices[i] = FALSE;
        for (int j = 0; j < numOfVertices; j++)
            graph[i][j] = FALSE;
    }
    while (fscanf(f, "%i %i", &first, &second) != EOF) 
        graph[first][second] = graph[second][first] = TRUE;
    DFS(0, graph, checkedVertices, numOfVertices, stack);
    fclose(f);
    free(checkedVertices);
    for (int i = 0; i < numOfVertices; i++)
        free(graph[i]);
    free(graph);
}
