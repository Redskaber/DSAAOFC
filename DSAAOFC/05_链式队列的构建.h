#pragma once

#ifndef __05_��ʽ���еĹ���_H__
	#define __05_��ʽ���еĹ���_H__
	
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


#endif // !__05_��ʽ���еĹ���_H__
