#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "06_stackµÄ¹¹½¨.h"



Rstatus stackInit(Stack* stack)
{
	/*
			stack 
		_
			|	|	
	cap = i	|	|	
			|	|
		-	-----	<- topInd = -1

		array = malloc()
	*/

	ElemType* array = NULL;
	int InitSize = Init_Capacity * sizeof(ElemType);
	array = (ElemType*)malloc(InitSize);

	assert(array != NULL);

	memset(array, Init_Mark, InitSize);

	stack->array = array;
	stack->topInd = -1;
	stack->capacity = Init_Capacity;

	return true;
}

Rstatus stackDestroy(Stack* stack)
{
	/*
		free(stack->array)
	*/
	free(stack->array);
	stack->array = NULL;
	stack->capacity = 0;
	stack->topInd = -1;
	return true;
}

Rstatus stack_up_capacity(Stack* stack)
{
	/*
			stack
			
			d4
		_
			|d3	|	<- topInd = -1 + 1
	cap = i	|d2	|
			|d1	|	
		-	-----
	
	ps: Ä¬ÈÏ2±¶À©ÈÝ
	*/
	if (stack->topInd == stack->capacity - 1)
	{
		int oldSize = stack->capacity * sizeof(ElemType);
		ElemType* NewArr = realloc(stack->array, Up_Capacity * oldSize);
		assert(NewArr != NULL);
		stack->array = NewArr;
		stack->capacity *= Up_Capacity;
	}
	return true;
}

Rstatus stackIsEmrty(Stack* stack)
{
	return stack->topInd == -1;
}

Rstatus stack_push(Stack* stack ,ElemType data)
{
	/*
			stack
		_
			|	|
	cap = i	|	|
			|d1	|	<- topInd = -1 + 1
		-	-----	

	*/
	stack_up_capacity(stack);		// Õ»Âú£¬ ÉÏÒç

	stack->array[stack->topInd + 1] = data;
	stack->topInd++;

	return true;
}

ElemType stack_pop(Stack* stack)
{
	/*
		stack
		_
			|	|
	cap = i	|	|
			|d1	|	<- topInd = 0 - 1
		-	-----	
	*/

	if (stack->topInd == -1) return false;		// Õ»¿Õ£¬ ÏÂÒç
	ElemType data =  stack->array[stack->topInd];
	stack->topInd--;
	return data;
}

Rstatus stackPrint(Stack* stack)
{
	for (int i = stack->topInd; i >= 0; i--)
	{
		printf("%d ", stack->array[i]);
	}
	printf("\n");
}