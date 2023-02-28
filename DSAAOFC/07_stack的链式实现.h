#pragma once


#ifndef __07_STACK����ʽʵ��_H__
	#define __07_STACK����ʽʵ��_H__
	
	/*
		ջ��									ջ��
		slp -> [data|ptr] -> [] ->... -> [] -> NULL; 
		front									rear

		����
		-> data{data,next}
		// -> stack{length,headElem}  ����ʹ��
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

#endif // !__07_STACK����ʽʵ��_H__
