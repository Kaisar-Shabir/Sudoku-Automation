#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int solutionNumber = 0;

//to display the solved sudoku
void fnDisp(int iArr[9][9]) {
	int i, j;

	printf("Solution number: %d\n", ++solutionNumber);
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			printf("%d\t", iArr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//checks if a number can be placed at the given (x, y) position
bool possible(int iArr[9][9], int x, int y, int num) {
	int i, j;

	//check if similar number occures in row x or column y
	for(i = 0; i < 9; i++) {
		if(iArr[i][y] == num || iArr[x][i] == num) {
			return false;
		}
	}

	i = x / 3;
	j = y / 3;

	i *= 3;
	j *= 3;

	int xC = 0;

	//checks if same number occures in the 3 x 3 grid
	while(xC < 3) {
		int yC = 0;
		while(yC < 3) {
			if(iArr[i + xC][j + yC] == num) {
				return false;
			}
			yC++;
		}
		xC++;
	}

	return true; 
}

//solve using backtracking
void fnSolve(int iArr[9][9]) {
	int i, j;

	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if(iArr[i][j] == 0) {
				int k;
				for(k = 0; k < 9; k++) {
					if(possible(iArr, i, j, k + 1)) {
						iArr[i][j] = k + 1;
						fnSolve(iArr);
						//if the solution was wrong go back to intial stage
						iArr[i][j] = 0;
					}
				}
				//if nun of the numbers could be placed here retyrn back to intial stage
				return;
			}
		}
	}

	//after filling all the rows and columns
	fnDisp(iArr);
}

int main() {

	//get the sudoku matrix from file q.txt
	int totalCases, curCase = 0;
	int iArr[9][9];
	FILE *fp;

	fp = fopen("q.txt", "r");
	fscanf(fp, "%d ", &totalCases);

	while(totalCases--) {
		int i, j;
		for(i = 0; i < 9; i++) {
			for(j = 0; j < 9; j++) {
				fscanf(fp, "%d ", &iArr[i][j]);
			}
		}
		//perform the operations
		printf("\t\t\tTest Case %d\n", ++curCase);
		solutionNumber = 0;
		fnSolve(iArr);
	}

	fclose(fp);

	return 0;
}
