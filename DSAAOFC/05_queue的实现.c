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
				- front �Ƴ�λ�ñ߽�����	(front == MaxSize -1) > 

			3.rear == front {ȫ����ȫ��}	-> length(ʵ����Ч����)
*/

static Rstatus frontEQrearHandle(SQueue* sq, ELemType data);
static Rstatus rearBorderHandle(SQueue* sq, ELemType data);

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

Rstatus frontEQrearHandle(SQueue* sq, ELemType data)
{
	/*
								front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    ����
		   -------------------------
								rear
					|ȫ�� |
					  v
			front
		   -------------------------
			[]	[]	[]	[]	[]	[1]	    ����
		   -------------------------
			rear

								front
		   -------------------------
			[1]	[2]	[3]	[4]	[5]	[6]	    ����
		   -------------------------
								rear
					|ȫ�� |
					  v
		   return error overflow
	
	PS:�ж� length ��ʵ�ʳ���
	*/
	if (sq->length)
	{
		printf("����������%zd = %d\n",sq->length, MaxSize);
		exit(0);
	}
	rearBorderHandle(sq, data);
	return true;
}

Rstatus rearBorderHandle(SQueue* sq, ELemType data)
{
	/*
					front
		   -------------------------
			[]	[]	[3]	[4]	[5]	[]	    ����
		   -------------------------
								rear

					front
		   -------------------------
			[]	[]	[3]	[4]	[]	[]	    ����
		   -------------------------
							rear
	
	*/
	sq->queue[sq->rear] = data;
	sq->length++;
	(sq->rear == MaxSize - 1) ? (sq->rear = 0) : (sq->rear++);
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

	ps: front != rear -> �϶��ܹ�����
		front == rear -> �ǲ��Ƕ�������
	*/
	if (sq->front == sq->rear) return frontEQrearHandle(sq, data);		// �߽�, ȫ����front = rear && length= MaxSize ������ȫ��(length = 0)��
	if (sq->front != sq->rear) return rearBorderHandle(sq, data);
	exit(0);
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
	if (!sq->length) 
	{
		printf("������Ԫ��! %zd %d", sq->length, MaxSize);
		exit(0);
	}
	// �ж� front �߽�����
	sq->queue[sq->front] = InitMark;
	sq->length--;

	if (sq->front == MaxSize - 1)
	{
		sq->front = 0;
		return true;
	}
	sq->front++;
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
