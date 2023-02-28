#include<stdio.h>
#include<stdlib.h>
#include "06_stackµÄ¹¹½¨.h"

/*
	stack_case
*/

int start_stack()
{
	Stack stack;
	
	stackInit(&stack);
	printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);
	stack_push(&stack, 10);
	stack_push(&stack, 20);
	stack_push(&stack, 30);
	stackPrint(&stack);

	for (int i = 4; i < 30; i++)
	{
		stack_push(&stack, i * 10);
		printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);
	}
	stackPrint(&stack);

	stack_pop(&stack);
	stackPrint(&stack);
	printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);

	printf("stackIsEmrty(&stack): %d\n", stackIsEmrty(&stack));

	int length = stack.topInd;
	for (int i = 0; i <= length; i++)
	{
		printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);
		stackPrint(&stack);
		stack_pop(&stack);
		stackPrint(&stack);
		printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);
	}

	printf("stackIsEmrty(&stack): %d\n", stackIsEmrty(&stack));


	printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);
	stackDestroy(&stack);
	printf("stack.capacity:%zd, stack.topInd:%d, stack.array:%p\n", stack.capacity, stack.topInd, stack.array);

	return 0;
}
