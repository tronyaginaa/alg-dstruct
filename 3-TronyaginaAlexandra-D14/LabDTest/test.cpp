#pragma once
#include "pch.h"
#include "LabDHeader.h"

/*
	OS: OS: Windows 10 Home, Version 20H2, Build 19042.1348
	IDE: Visual Studio 2019 Community Edition
	CPU: Intel(R) Core(TM) i5-1038NG7 CPU 2.00GHz
	RAM: 16 GB

	RESULTS:
	GRAPH TRAVERSAL TIME: 123061 ms
	USED MEMORY:  471 MB
*/

TEST(FunctionalTest, SudokuWithoutSolution) {
	sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
	ASSERT_TRUE(sudoku);
	FILE* file = fopen("NotSolutionTest.txt", "r");
	ASSERT_TRUE(file);
	fscanf(file, "%i", &sudoku->n);
	sudoku->n *= sudoku->n;
	sudoku->cells = (int**)malloc(sudoku->n * sizeof(int*));
	ASSERT_TRUE(sudoku->cells);
	for (int i = 0; i < sudoku->n; i++) {
		sudoku->cells[i] = (int*)malloc(sudoku->n * sizeof(int));
		if (!sudoku->cells[i]) {
			for (int j = 0; j < sudoku->n; j++)
				free(sudoku->cells[i]);
			free(sudoku->cells);
			free(sudoku);
			fclose(file);
			ASSERT_TRUE(sudoku);
		}
	}
	for (int i = 0; i < sudoku->n; i++)
		for (int j = 0; j < sudoku->n; j++)
			fscanf(file, "%i", &sudoku->cells[i][j]);
	fclose(file);
	sudoku->solved = FALSE;
	sudokuSolution(sudoku, 1, 0, 0);
	ASSERT_TRUE(!sudoku->solved);
}

//Test fo sudoku 4x4
TEST(FunctionalTest, SudokuWithSomeSolution_Test1) {
	sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
	ASSERT_TRUE(sudoku);
	FILE* file = fopen("SolutionTest.txt", "r");
	ASSERT_TRUE(file);
	fscanf(file, "%i", &sudoku->n);
	sudoku->n *= sudoku->n;
	sudoku->cells = (int**)malloc(sudoku->n * sizeof(int*));
	ASSERT_TRUE(sudoku->cells);
	for (int i = 0; i < sudoku->n; i++) {
		sudoku->cells[i] = (int*)malloc(sudoku->n * sizeof(int));
		if (!sudoku->cells[i]) {
			for (int j = 0; j < sudoku->n; j++)
				free(sudoku->cells[i]);
			free(sudoku->cells);
			free(sudoku);
			fclose(file);
			ASSERT_TRUE(sudoku);
		}
	}
	for (int i = 0; i < sudoku->n; i++)
		for (int j = 0; j < sudoku->n; j++)
			fscanf(file, "%i", &sudoku->cells[i][j]);
	fclose(file);
	sudoku->solved = FALSE;
	sudokuSolution(sudoku, 1, 0, 0);
	ASSERT_TRUE(sudoku->solved);
}

//Test for sudoku 9x9
TEST(FunctionalTest, SudokuWithSomeSolution_Test2) {
	sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
	ASSERT_TRUE(sudoku);
	FILE* file = fopen("SolutionTest.txt", "r");
	ASSERT_TRUE(file);
	fscanf(file, "%i", &sudoku->n);
	sudoku->n *= sudoku->n;
	sudoku->cells = (int**)malloc(sudoku->n * sizeof(int*));
	ASSERT_TRUE(sudoku->cells);
	for (int i = 0; i < sudoku->n; i++) {
		sudoku->cells[i] = (int*)malloc(sudoku->n * sizeof(int));
		if (!sudoku->cells[i]) {
			for (int j = 0; j < sudoku->n; j++)
				free(sudoku->cells[i]);
			free(sudoku->cells);
			free(sudoku);
			fclose(file);
			ASSERT_TRUE(sudoku);
		}
	}
	for (int i = 0; i < sudoku->n; i++)
		for (int j = 0; j < sudoku->n; j++)
			fscanf(file, "%i", &sudoku->cells[i][j]);
	fclose(file);
	sudoku->solved = FALSE;
	sudokuSolution(sudoku, 1, 0, 0);
	ASSERT_TRUE(sudoku->solved);
}

TEST(StreeTest, SudokuStressTest) {
	sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
	ASSERT_TRUE(sudoku);
	FILE* file = fopen("StressTest.txt", "r");
	ASSERT_TRUE(file);
	fscanf(file, "%i", &sudoku->n);
	sudoku->n *= sudoku->n;
	sudoku->cells = (int**)malloc(sudoku->n * sizeof(int*));
	ASSERT_TRUE(sudoku->cells);
	for (int i = 0; i < sudoku->n; i++) {
		sudoku->cells[i] = (int*)malloc(sudoku->n * sizeof(int));
		if (!sudoku->cells[i]) {
			for (int j = 0; j < sudoku->n; j++)
				free(sudoku->cells[i]);
			free(sudoku->cells);
			free(sudoku);
			fclose(file);
			ASSERT_TRUE(sudoku);
		}
	}
	for (int i = 0; i < sudoku->n; i++)
		for (int j = 0; j < sudoku->n; j++)
			fscanf(file, "%i", &sudoku->cells[i][j]);
	fclose(file);
	sudoku->solved = FALSE;
	sudokuSolution(sudoku, 1, 0, 0);
}

