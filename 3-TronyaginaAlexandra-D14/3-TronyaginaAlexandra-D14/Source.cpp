
#include "LabDHeader.h"

#define TRUE 1
#define FALSE (!TRUE)


sudoku_t* readFile(FILE* file) {
	sudoku_t* sudoku = (sudoku_t*)malloc(sizeof(sudoku_t));
	if (!sudoku)
		return NULL;
	fscanf(file, "%i", &sudoku->n);
	sudoku->n *= sudoku->n;
	sudoku->cells = (int**)malloc(sudoku->n * sizeof(int*));
	if (!sudoku->cells) {
		fclose(file);
		return NULL;
	}
	for (int i = 0; i < sudoku->n; i++) {
		sudoku->cells[i] = (int*)malloc(sudoku->n * sizeof(int));
		if (!sudoku->cells[i]) {
			for (int j = 0; j < sudoku->n; j++)
				free(sudoku->cells[j]);
			free(sudoku->cells);
			fclose(file);
			return NULL;
		}
	}
	for (int i = 0; i < sudoku->n; i++)
		for (int j = 0; j < sudoku->n; j++)
			fscanf(file, "%i", &sudoku->cells[i][j]);
	fclose(file);
	sudoku->solved = FALSE;
	return sudoku;
}


void printFile(FILE* file, sudoku_t* sudoku) {
	if (!sudoku->solved)
		fprintf(file, "%i", 0);
	else
		for (int i = 0; i < sudoku->n; i++) {
			for (int j = 0; j < sudoku->n; j++)
				fprintf(file, "%i ", sudoku->cells[i][j]);
			fprintf(file, "\n");
		}
	fclose(file);
	return;
}


int cellCheck(sudoku_t* sudoku, int column, int row, int num) {
	int quadrant = sqrt(sudoku->n);
	for (int i = 0; i < sudoku->n; i++)
		if (sudoku->cells[i][column] == num || sudoku->cells[row][i] == num)
			return FALSE;
	for (int i = 0; i < sudoku->n; i += quadrant)
		if (i + quadrant > row) {
			row = i;
			break;
		}
	for (int i = 0; i < sudoku->n; i += quadrant)
		if (i + quadrant > column) {
			column = i;
			break;
		}
	for (int i = row; i < row + quadrant; i++)
		for (int j = column; j < column + quadrant; j++)
			if (sudoku->cells[i][j] == num)
				return FALSE;
	return TRUE;
}


void sudokuSolution(sudoku_t* sudoku, int num, int row, int column) {
	for (; row < sudoku->n; row++)
		for (column = 0; column < sudoku->n; column++)
			if (sudoku->cells[row][column] == 0)
				while (num <= sudoku->n && !sudoku->solved) {
					if (cellCheck(sudoku, column, row, num)) {
						sudoku->cells[row][column] = num;
						if (row + 1 == sudoku->n && column + 1 == sudoku->n)
							sudoku->solved = TRUE;
						else {
							sudokuSolution(sudoku, 1, row, 0);
							if (!sudoku->solved)
								sudoku->cells[row][column] = 0;
						}
					}
					num++;
				}
	return;
}


void freeSudoku(sudoku_t* sudoku) {
	for (int i = 0; i < sudoku->n; i++)
		free(sudoku->cells[i]);
	free(sudoku->cells);
	free(sudoku);
}

void sol(char const* inputFileName, char const* outputFileName) {
	FILE* input = fopen(inputFileName, "r");
	if (!input)
		return;
	FILE* output = fopen(outputFileName, "w");
	if (!output) {
		fclose(input);
		return;
	}
	sudoku_t sudoku = readFile(input);
	sudokuSolution(sudoku, 1, 0, 0);
	printFile(output, sudoku);
	freeSudoku(sudoku);
	fclose(input);
	fclose(output);
	return;
}
