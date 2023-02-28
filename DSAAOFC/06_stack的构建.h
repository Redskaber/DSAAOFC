#pragma once

#ifndef __06_STACK�Ĺ���_H__
	#define __06_STACK�Ĺ���_H__
	
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
	* ��̬˳��ջ
		#define MaxSize 20
		typedef struct STACK
		{
			ElemType* array[MaxSize];
			int topInd;
		}Stack;
	*/

	// ��̬˳��ջ
	typedef struct STACK
	{
		ElemType* array;
		int topInd;
		size_t capacity;
	}Stack;

	/*
		init
		����
	�ṩ��
		ѹջ
		��ջ
	*/

	extern Rstatus stackInit(Stack* stack);
	extern Rstatus stackDestroy(Stack* stack);

	extern Rstatus stackIsEmrty(Stack* stack);
	extern Rstatus stack_up_capacity(Stack* stack);

	extern Rstatus stack_push(Stack* stack, ElemType data);
	extern ElemType stack_pop(Stack* stack);

	extern Rstatus stackPrint(Stack* stack);

#endif // !__06_STACK�Ĺ���_H__


