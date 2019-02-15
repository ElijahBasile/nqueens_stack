/*
 * nqueens.h
 *
 *  Created on: Jan 30, 2019
 *      Author: Elijah Basile
 */

#ifndef NQUEENS_H_
#define NQUEENS_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"

void nQueens(int);
int setBoardSize();
void printQCoordinates (int*, int, int);
int* createQCoordinates(int);
bool testForGuard(int,int,int*,int);
void printBoard(int* , int );

// follows the PsuedoCode model described in the Chapter 3 lecture
void nQueens(int boardSize) {
	STACK* available = createStack();

	int* curCoord = (int*)malloc(sizeof(int)*2);

	int* qCoord = createQCoordinates(boardSize);

	int row = 1;
	int col = 0;

	while (row <= boardSize) {
		int stepNumber = 0;
		while(col <= boardSize && row <= boardSize) {
			stepNumber++;
			col++;
			if(!testForGuard(row,col,qCoord,boardSize)) {
				//place queen at row-col intersection on board
				int* location = qCoord+(row-1);
				*location = col;
				//setting the row-col data onto the stack
				*curCoord = row;
				curCoord++;
				*curCoord = col;
				curCoord--;

				push(&(available->top),&curCoord);
				//increment row and set the column to zero
				row++;
				col = 0;
			}
			//At end of row. Back up to previous position
			while(col >= boardSize) {
				int* coords = pop(&(available->top));
				int* location = qCoord+row-1;
				*location = -1;
				row = *coords;
				(coords)++;
				col = *coords;
				free(coords);
			}
			printQCoordinates(qCoord,boardSize,stepNumber);
		}
	}
	printBoard(qCoord,boardSize);

	// deallocate memory at end of function
	free(curCoord);
	free(qCoord);
	free(qCoord);
	deleteStack(&available);

	//exit
	return;
}

//prints the board in a matrix form
void printBoard(int* qCoord, int boardSize) {
	printf("Solution:\n");
	for (int i = 1 ; i <= boardSize ; i++)
		printf("	%d",i);
	printf("\n");
	for (int i = 1; i <= boardSize ; qCoord++,i++) {
		printf("%d	",i);
		for (int j = 1 ; j <= boardSize ; j++) {
			if (j == *qCoord)
				printf("Q	");
			else
				printf("_	");
		}
		printf("\n");
	}

	return;
}

// tests if a space is guarded horizontally or diagonally by another placed queen
bool testForGuard(int row, int col,int* qCoord, int boardSize) {
	for (int i = 1; i <= boardSize; i++) {
		if (*(qCoord+i-1) == -1)
			continue;
		if (col == *(qCoord+i-1))
			return true;
		if (abs(i - row) == abs(*(qCoord+i-1) - col))
			return true;
	}
	return false;
}

// sets the board size and the number of queens in the board
int setBoardSize() {
	int boardSize;
	int keepGoing = 1;

	// prompt the user to enter n number of queens
	while (keepGoing) {
		printf("Please enter the number of queens on the board: ");

		fflush(stdin);
		scanf("%d",&boardSize);
		keepGoing = 0;

		if (boardSize <= 0) {
			printf("please enter a number that is greater than 0\n");
			keepGoing = 1;
		}
	}
	return boardSize;
}

//This prints the coordinates out to the screen
void printQCoordinates (int* qCoord, int queenAmount, int stepNumber) {
	printf("Step %d: QC [",stepNumber);
	for (int i = 0; i < queenAmount ; i++) {
		printf("%d",*(qCoord+i));
		if((1+i)!=queenAmount)
			printf(",");
	}
	printf("]\n");
}

//initializes the list of queen coordinates
int* createQCoordinates(int queenAmount) {
	int* qCoord = (int*)malloc(sizeof(int)*queenAmount);

	for(int i = 0; i<queenAmount; i++) {
		*(qCoord+i) = -1;
	}

	return qCoord;
}




#endif /* NQUEENS_H_ */
