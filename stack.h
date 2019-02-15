/*
 * stack.h
 *
 *  Created on: Jan 30, 2019
 *      Author: Elijah Basile
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//node of the stack
typedef struct node {
	int* data;
	struct node* link;
} STACK_NODE;

//the handle for the stack
typedef struct {
	int count;
	STACK_NODE* top;
} STACK;

STACK* createStack ();
bool push(STACK_NODE** , int** );
int* pop(STACK_NODE** );
void deleteStack(STACK** );

//	builds a new stack data structure
STACK* createStack (void) {
	STACK* stack;

	stack = (STACK*)malloc(sizeof(STACK));

	if (stack) {
		stack->count = 0;
		stack->top = NULL;
	} // if
	return stack;
}

//pushes a new item to the top of the stack
bool push(STACK_NODE** pStackTop, int** coords) {

	//local declarations
	STACK_NODE* pNew;
	bool success;

	pNew = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if(!pNew)
		success = false;
	else {
		//initializing data pointer
		pNew->data = (int*)malloc(sizeof(int)*2);
		*(pNew->data) = **coords;
		(pNew->data)++;
		*(pNew->data) = *(*coords+1);
		(pNew->data)--;

		pNew->link = *pStackTop;
		*pStackTop = pNew;
		success = true;
	} // else
	return success;
}

//this removes the top item from the stack, returning its data
int* pop(STACK_NODE** pStackTop) {
	STACK_NODE* pDlt;
	int* coords;

	if (*pStackTop) {
		int* data = (*pStackTop)->data;
		coords = data;
		pDlt = *pStackTop;
		*pStackTop = (*pStackTop)->link;
		free(pDlt->data);
		free(pDlt);
	} else {
		printf("Solution unable to be solved with \nthe given amount of queens.\n");
		exit(0);
	}

	return coords;
}

//this deallocates all memory associated with the stack
void deleteStack(STACK** stack) {
	do {
		if((*stack)->top->link == NULL) {
			free(*stack);
		} else {
			free(((*stack)->top->data));
			pop(&((*stack)->top));
		}
	} while ((*stack)->top->link != NULL);
}


#endif /* STACK_H_ */
