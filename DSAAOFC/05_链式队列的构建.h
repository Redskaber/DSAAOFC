#pragma once

#ifndef __05_链式队列的构建_H__
	#define __05_链式队列的构建_H__
	
	typedef int Rstatus;
	typedef int ElemType;

	typedef struct QUEUENODE
	{
		ElemType data;
		struct QueueNode* next;
	}QueueNode, *QueueElem;

	typedef struct LINKQUEUE
	{
		QueueElem headNode;
		QueueElem endNode;
	}LinkQueue;

	extern Rstatus LinkQueueInit(LinkQueue* lq);
	extern Rstatus LinkQueueFrontPush(LinkQueue* lq, ElemType data);
	extern Rstatus LinkQueueFrontPop(LinkQueue* lq);
	extern Rstatus LinkQueuePrint(LinkQueue* lq);


#endif // !__05_链式队列的构建_H__
