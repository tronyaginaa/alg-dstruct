#pragma once

#pragma warning(disable: 4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE (!TRUE)

	typedef struct {
		int** cells;
		int n;
		int solved;
	}sudoku_t;

	sudoku_t* readFile(FILE* file);
	void printFile(FILE* fileName, sudoku_t* sudoku);
	int cellCheck(sudoku_t* sudoku, int column, int row, int num);
	void sudokuSolution(sudoku_t* sudoku, int num, int row, int column);
	void freeSudoku(sudoku_t* sudoku);
	void sol(const char* inputFileName, const char* outputFileName);

#ifdef __cplusplus
}
#endif
