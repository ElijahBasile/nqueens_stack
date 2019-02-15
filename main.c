// N Queen's Implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "nqueens.h"

int main() {
	//required command that makes the scanf and printf work properly
	setvbuf(stdout,  NULL,  _IONBF,  0);

	//set the board size
	int boardSize = setBoardSize();

	// find the solution to the N Queens Problem and print the board for the user
	nQueens(boardSize);

	//exit
	return 0;
}
