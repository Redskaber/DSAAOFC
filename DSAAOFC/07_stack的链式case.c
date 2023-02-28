#include<stdio.h>
#include<stdlib.h>
#include "07_stack的链式实现.h"


int start_stack_of_link()
{
	LinkStack stack;
	linkStackInit(&stack);
	printf("%p\n",stack.next);

	linkStackPush(&stack, 100);
	linkStackPush(&stack, 200);
	linkStackPush(&stack, 300);
	linkStackPush(&stack, 400);
	linkStackPrint(&stack);

	for (int i = 5; i < 30; i++)
	{
		linkStackPush(&stack,i*10);
		linkStackPrint(&stack);
	}

	linkStackPop(&stack);
	linkStackPrint(&stack);
	linkStackPop(&stack);
	linkStackPrint(&stack);

	linkStackPop(&stack);
	linkStackPop(&stack);
	linkStackPop(&stack);
	linkStackPop(&stack);
	linkStackPop(&stack);
	linkStackPrint(&stack);

	return 0;
}

