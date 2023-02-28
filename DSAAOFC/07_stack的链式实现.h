#pragma once


#ifndef __07_STACK的链式实现_H__
	#define __07_STACK的链式实现_H__
	
	/*
		栈顶									栈底
		slp -> [data|ptr] -> [] ->... -> [] -> NULL; 
		front									rear

		分析
		-> data{data,next}
		// -> stack{length,headElem}  可以使用
	*/
		
	typedef int ElemType;
	typedef int Rstatus;

	typedef struct LINKSTACK
	{
		ElemType data;
		struct LinkStack* next;
	}LinkStack;

	extern Rstatus linkStackInit(LinkStack* linkstack);
	extern LinkStack* createLinkStackElem(ElemType data);
	extern Rstatus linkStackPush(LinkStack* linkstack, ElemType data);
	extern Rstatus linkStackPop(LinkStack* linkstack);

	extern Rstatus linkStackPrint(LinkStack* linkstack);

#endif // !__07_STACK的链式实现_H__
