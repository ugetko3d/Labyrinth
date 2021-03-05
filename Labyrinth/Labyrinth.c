#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool solve(int row, int col, char **labyrinth);
bool validMove(int row, int col, char **labyrinth);
void printLabyrinth(char **labyrinth);

char FRI = '0';
char STENGT = '1';
char HOYRE = '>';
char NED = 'v';
char VENSTRE = '<';
char OPP = '^';
char BRUKT = 'X';
int n;

int main() {

	printf("Enter an integer n, which will represent a nxn maze:\n");
	scanf("%d", &n);

	char **labyrinth = calloc(n, n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		labyrinth[i] = calloc(n, n * sizeof(char));
	}

	time_t t;
	srand((unsigned)time(&t));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int r = rand() % 10;
			if (r < 4) {
				labyrinth[i][j] = STENGT;
			}
			else {
				labyrinth[i][j] = FRI;
			}
		}
	}

	labyrinth[0][0] = FRI;
	labyrinth[n - 1][n - 1] = FRI;

	printLabyrinth(labyrinth);

	if (solve(0, 0, labyrinth)) {
		printf("%s\n", "We found our way through the labyrinth!");
		printLabyrinth(labyrinth);
		return 1;
	}

	else {
		printf("%s\n", "There's no way through the labyrinth.");
		printLabyrinth(labyrinth);
		return 0;
	}

}

bool solve(int row, int col, char **labyrinth) {

	if (row == (n - 1) && col == (n - 1)) {
		labyrinth[row][col] = BRUKT;
		return true;
	}

	labyrinth[row][col] = BRUKT;

	//EAST
	if (validMove(row, (col + 1), labyrinth)) {
		if (solve(row, (col + 1), labyrinth)) {
			labyrinth[row][col] = HOYRE;
			return true;
		}
	}
	//SOUTH
	if (validMove((row + 1), col, labyrinth)) {
		if (solve((row + 1), col, labyrinth)) {
			labyrinth[row][col] = NED;
			return true;
		}
	}
	//WEST
	if (validMove(row, (col - 1), labyrinth)) {
		if (solve(row, (col - 1), labyrinth)) {
			labyrinth[row][col] = VENSTRE;
			return true;
		}
	}
	//NORTH
	if (validMove((row - 1), col, labyrinth)) {
		if (solve((row - 1), col, labyrinth)) {
			labyrinth[row][col] = OPP;
			return true;
		}
	}
	return false;
}

bool validMove(int row, int col, char **labyrinth) {
	if (row >= 0 && row < n && col >= 0 && col < n) {
		return labyrinth[row][col] == FRI;
	}
	return false;
}

void printLabyrinth(char **labyrinth) {
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c%c%c", ' ', labyrinth[i][j], ' ');
		}
		printf("\n");
	}
	printf("\n");
}