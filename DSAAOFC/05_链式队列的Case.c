#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "05_��ʽ���еĹ���.h"



int start_LinkQueue()
{

	LinkQueue lq;
	LinkQueueInit(&lq);
	printf(" lq.headNode:%p, lq.endNode:%p\n", lq.headNode, lq.endNode);
	LinkQueueFrontPush(&lq,100);
	LinkQueueFrontPush(&lq,200);
	LinkQueueFrontPush(&lq,300);
	LinkQueuePrint(&lq);
	LinkQueueFrontPush(&lq, 400);
	LinkQueueFrontPush(&lq, 500);
	LinkQueuePrint(&lq);

	LinkQueueFrontPop(&lq);
	LinkQueueFrontPop(&lq);
	LinkQueueFrontPop(&lq);
	LinkQueuePrint(&lq);
	LinkQueueFrontPop(&lq);
	LinkQueueFrontPop(&lq);
	
	//LinkQueueFrontPop(&lq);		// �����

	return 0;
}