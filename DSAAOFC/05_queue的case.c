#include<stdio.h>
#include<stdlib.h>
#include "05_queue��ʵ��.h"


int start_queue()
{
	SQueue sq;
	staticQueueInit(&sq);
	staticQueuePrint(&sq);
	printf("front:%d\trear:%d length:%zd\n", (int)sq.front,(int)sq.rear, sq.length);
	staticQueueRearPush(&sq,100);
	staticQueuePrint(&sq);
	printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);

	for (int i = 2; i <= MaxSize; i++)
	{
		staticQueueRearPush(&sq, i*100);
		staticQueuePrint(&sq);
		printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);
	}

	//staticQueueRearPush(&sq, 100);
	//staticQueuePrint(&sq);
	//printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);


	staticQueueFrontPop(&sq);
	staticQueuePrint(&sq);
	printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);

	for (int i = 2; i <= MaxSize; i++)
	{
		staticQueueFrontPop(&sq);
		staticQueuePrint(&sq);
		printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);
	}

	//staticQueueFrontPop(&sq);
	//staticQueuePrint(&sq);
	//printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);

	printf("\n��̬˳��ѭ�����в���(ȫ��):\n");
	for (int i = 1; i < 2*MaxSize; i++)
	{
		staticQueueRearPush(&sq, i * 100);
		staticQueueFrontPop(&sq);
		printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);
	}


	printf("\n��̬˳��ѭ�����в���(ѭ��):\n");
	
	for (int i = 1; i < 2*MaxSize; i++)
	{
		if (i < 8) staticQueueRearPush(&sq, i * 100);
		else if (i < 11) staticQueueFrontPop(&sq);
		else
		{
			staticQueueRearPush(&sq, i * 100);
			staticQueueFrontPop(&sq);
		}
		staticQueuePrint(&sq);
		printf("front:%d\trear:%d length:%zd\n", (int)sq.front, (int)sq.rear, sq.length);
	}

	return 0;
}
