#include<iostream>
using namespace std;

//Global Declarations
const int COLSIZE = 8;
const int ROWSIZE = 8;
int board[ROWSIZE][COLSIZE];	//solution board(1 for queen, 0 for empty)
bool blocked[ROWSIZE][COLSIZE];	//keeps track of what locations are blocked(t, f)
int tracks[ROWSIZE];	//keeps track of attempted columns in a given row(counter)

//Function Protoypes
void findSolution(int row);
int findCol(int row);
void setBlockedFrom(int row, int col);
void resetBlocked();
void clearTracksAfter(int row);	
void printSolution();

int main() {
	// initialize the arrays
	for (int i = 0; i < ROWSIZE; i++) {
		tracks[i] = 0;
		for (int j = 0; j < COLSIZE; j++) {
			board[i][j] = 0;
			blocked[i][j] = false;
		}
	}
	findSolution(0);
	system("pause");
	return 0;
}

void findSolution(int row) {
	if (row >= ROWSIZE) {
		//if solution found
		printSolution();
		return;
	}
	int col = findCol(row);
	if (col == -1) {
		//if no solution in row, backtrack
		board[row - 1][tracks[row - 1]] = 0;
		tracks[row - 1]++;
		clearTracksAfter(row - 1);
		resetBlocked();
		findSolution(row - 1);
	} 
	else {
		//if solution in row found
		board[row][col] = 1;
		setBlockedFrom(row, col);
		tracks[row] = col;
		findSolution(row + 1);
	}
}

// Returns a column num to place queen in specified row(returns -1 for no solution)
int findCol(int row) {
	for (int i = tracks[row]; i < COLSIZE; i++) {
		if (!blocked[row][i]) {
			return i;
		}
	}
	return -1;
}

// Sets blocked spots from a given coordinate
void setBlockedFrom(int row, int col) {
	//Set horizontal
	for (int i = 0; i < ROWSIZE; i++) {
		blocked[i][col] = true;
	}

	//Set verticle
	for (int i = 0; i < COLSIZE; i++) {
		blocked[row][i] = true;
	}

	//Set Diag(top-left)
	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
		blocked[i][j] = true;
	}

	//Set Diag(top-right)
	for (int i = row, j = col; i < ROWSIZE && j < COLSIZE; i++, j++) {
		blocked[i][j] = true;
	}

	//Diag(bot-left)
	for (int i = row, j = col; i >= 0 && j < COLSIZE; i--, j++) {
		blocked[i][j] = true;
	}

	//Set Diag(bot-right)
	for (int i = row, j = col; i < ROWSIZE && j >= 0; i++, j--) {
		blocked[i][j] = true;
	}
}

// Resets blocked array and re-initializes it(used when back-tracking)
void resetBlocked() {
	//reset entire blocked array
	for (int i = 0; i < ROWSIZE; i++) {
		for (int j = 0; j < COLSIZE; j++) {
			blocked[i][j] = false;
		}
	}
	//set blocked from found queen locations
	for (int i = 0; i < ROWSIZE; i++) {
		for (int j = 0; j < COLSIZE; j++) {
			if (board[i][j] == 1) {
				setBlockedFrom(i, j);
			}
		}
	}
}

// Clears tracks after a specified row (used when back tracking)
void clearTracksAfter(int row) {
	for (int i = row+1; i < ROWSIZE; i++) {
		tracks[i] = 0;
	}
}

void printSolution(){
	cout << endl;
	for (int i = 0; i < ROWSIZE; i++) {
		for (int j = 0; j < COLSIZE; j++) {
			if (board[i][j] == 1) {
				cout << "Q ";
				continue;
			}
			else if (blocked[i][j]) {
				cout << "x ";
				continue;
			}
			else {
				cout << "0 ";
				continue;
			}
		}
		cout << endl;
	}
}