#pragma once

#ifndef __06_STACK的构建_H__
	#define __06_STACK的构建_H__
	
	/*
		stack 
		_
			|	|	
		cap	|d1	|	<- top
			|d0	|
		-	-----
	*/

	typedef int Rstatus;
	typedef int ElemType;

	#define Init_Capacity 20
	#define Init_Mark 0
	#define Up_Capacity 2

	/*
	* 静态顺序栈
		#define MaxSize 20
		typedef struct STACK
		{
			ElemType* array[MaxSize];
			int topInd;
		}Stack;
	*/

	// 动态顺序栈
	typedef struct STACK
	{
		ElemType* array;
		int topInd;
		size_t capacity;
	}Stack;

	/*
		init
		扩容
	提供：
		压栈
		弹栈
	*/

	extern Rstatus stackInit(Stack* stack);
	extern Rstatus stackDestroy(Stack* stack);

	extern Rstatus stackIsEmrty(Stack* stack);
	extern Rstatus stack_up_capacity(Stack* stack);

	extern Rstatus stack_push(Stack* stack, ElemType data);
	extern ElemType stack_pop(Stack* stack);

	extern Rstatus stackPrint(Stack* stack);

#endif // !__06_STACK的构建_H__


