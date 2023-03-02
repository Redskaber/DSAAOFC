#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "05_queue��ʵ��.h"

/*
		   -------------------------
			[]	[]	[]	[]	[]	[]	    ����
		   -------------------------
			�� ->	����	->��		���Ƚ��ȳ���

			��̬ѭ��˳����� ���� + �ṹ��

			1.��ʼ��
			2.�߽����⴦��
				- rear ����λ�ñ߽�����		(rear == MaxSize -1) > 	(sq->rear == MaxSize - 1) ? (sq->rear = 0) : (sq->rear++);
				- front �Ƴ�λ�ñ߽�����	(front == MaxSize -1) >  (sq->front == MaxSize - 1) ? (sq->front = 0) : (sq->front++);
	
			3.rear == front {ȫ����ȫ��}	-> length(ʵ����Ч����)
*/


Rstatus staticQueueInit(SQueue* sq)
{
	/*
			front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    ����
		   -------------------------
			rear
	init:
		memeset(array)
		front = rear = 0;
	*/
	memset(sq->queue, InitMark, sizeof(sq->queue));
	sq->front = sq->rear = sq->length = 0;
	return true;
}

Rstatus staticQueueRearPush(SQueue* sq, ELemType data)
{
	/*
			front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    ����
		   -------------------------
			rear

			front
		   -------------------------
			[1]	[]	[]	[]	[]	[]	    ����
		   -------------------------
				rear = 1
	*/
	if (sq->length == MaxSize)		// �߽�, �����
	{
		printf("����������%zd = %d\n", sq->length, MaxSize);
		exit(0);
	}
	sq->queue[sq->rear] = data;
	sq->length++;
	(sq->rear == MaxSize - 1) ? (sq->rear = 0) : (sq->rear++); // �ж� rear �߽�����

	return true;
}

Rstatus staticQueueFrontPop(SQueue* sq)
{
	/*
			front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    ����
		   -------------------------
			rear

			front
		   -------------------------
			[1]	[]	[]	[]	[]	[]	    ����
		   -------------------------
				rear = 1

	1. �ն��У�sq->length = 0��
	2. �ǿն��У�sq->length != 0��

	*/
	if (!sq->length)	// �����
	{
		printf("������Ԫ��! %zd %d", sq->length, MaxSize);
		exit(0);
	}
	
	sq->queue[sq->front] = InitMark;
	sq->length--;
	(sq->front == MaxSize - 1) ? (sq->front = 0) : (sq->front++);	// �ж� front �߽�����
	return true;
}

Rstatus staticQueuePrint(SQueue* sq)
{
	for (int i = 0; i < MaxSize; i++)
	{
		printf("%d ",sq->queue[i]);
	}
	printf("\n");
}
