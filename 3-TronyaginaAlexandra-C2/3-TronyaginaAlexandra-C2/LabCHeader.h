
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	#pragma warning (disable:4996)
	#include <stdio.h>
	#include <stdlib.h>

	#define TRUE 1
	#define FALSE (!TRUE)

	void feelGraph();
	void memoryInit();
	void memoryFree();
	void readGraph();
	void DFS(int num, int** graph, int* chekedVertices, int numOfVertices);
	

#ifdef __cplusplus
}
#endif
