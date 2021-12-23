#pragma once
#include "pch.h"
#include "LabDHeader.h"

/*
	OS: OS: Windows 10 Home, Version 20H2, Build 19042.1348
	IDE: Visual Studio 2019 Community Edition
	CPU: Intel(R) Core(TM) i5-1038NG7 CPU 2.00GHz
	RAM: 16 GB

	RESULTS:
	GRAPH TRAVERSAL TIME: 124502 ms
	USED MEMORY:  471 MB
*/

TEST(FunctionalTest, SudokuWithoutSolution) {
	sol("testSudoku_noSolution.txt", "output_noSolution.txt");
	FILE* result = fopen("output_noSolution.txt", "r");
	ASSERT_TRUE(result);
	fseek(result, 0, SEEK_END);
	int i = ftell(result);
	EXPECT_EQ(i, 1);
	fscanf(result, "%i", i);
	EXPECT_EQ(i, 0);
}

//Test fo sudoku 4x4
TEST(FunctionalTest, SudokuWithSomeSolution_Test1) {
	sol("testSudoku_2.txt", "output_sudoku_2.txt");
	FILE* result = fopen("output_sudoku_2.txt", "r");
	ASSERT_TRUE(result);
	FILE* expected = fopen("expected_sudoku_2.txt", "r");
	ASSERT_TRUE(result);
	fseek(result, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	EXPECT_EQ(ftell(result), ftell(expected));
	fseek(result, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	int result_cell, expected_sell;
	while (fscanf(result, "%i", result_cell) != EOF && fscanf(result, "%i", result_cell) != EOF) {
		EXPECT_EQ(result_cell, expected_cell);
	}
	fclose(result);
	fclose(expected);
}

//Test for sudoku 9x9
TEST(FunctionalTest, SudokuWithSomeSolution_Test2) {
	sol("testSudoku_3.txt", "output_sudoku_3.txt");
	FILE* result = fopen("output_sudoku_3.txt", "r");
	ASSERT_TRUE(result);
	FILE* expected = fopen("expected_sudoku_3.txt", "r");
	ASSERT_TRUE(result);
	fseek(result, 0, SEEK_END);
	fseek(expected, 0, SEEK_END);
	EXPECT_EQ(ftell(result), ftell(expected));
	fseek(result, 0, SEEK_SET);
	fseek(expected, 0, SEEK_SET);
	int result_cell, expected_sell;
	while (fscanf(result, "%i", result_cell) != EOF && fscanf(result, "%i", result_cell) != EOF) {
		EXPECT_EQ(result_cell, expected_cell);
	}
	fclose(result);
	fclose(expected);
}

TEST(StreeTest, SudokuStressTest) {
	sol("testSudoku_stressTest.txt", "output_stressTest.txt");
}

