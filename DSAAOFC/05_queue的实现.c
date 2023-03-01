#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include "05_queue的实现.h"

/*
		   -------------------------
			[]	[]	[]	[]	[]	[]	    队列
		   -------------------------
			进 ->	队列	->出		（先进先出）

			静态循环顺序队列 数组 + 结构体

			1.初始化
			2.边界问题处理
				- rear 插入位置边界问题		(rear == MaxSize -1) > 	(sq->rear == MaxSize - 1) ? (sq->rear = 0) : (sq->rear++);
				- front 移除位置边界问题	(front == MaxSize -1) > 

			3.rear == front {全满，全空}	-> length(实际有效个数)
*/

static Rstatus frontEQrearHandle(SQueue* sq, ELemType data);
static Rstatus rearBorderHandle(SQueue* sq, ELemType data);

Rstatus staticQueueInit(SQueue* sq)
{
	/*
			front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    队列
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
			[]	[]	[]	[]	[]	[]	    队列
		   -------------------------
								rear
					|全空 |
					  v
			front
		   -------------------------
			[]	[]	[]	[]	[]	[1]	    队列
		   -------------------------
			rear

								front
		   -------------------------
			[1]	[2]	[3]	[4]	[5]	[6]	    队列
		   -------------------------
								rear
					|全满 |
					  v
		   return error overflow
	
	PS:判断 length 的实际长度
	*/
	if (sq->length)
	{
		printf("队列已满！%zd = %d\n",sq->length, MaxSize);
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
			[]	[]	[3]	[4]	[5]	[]	    队列
		   -------------------------
								rear

					front
		   -------------------------
			[]	[]	[3]	[4]	[]	[]	    队列
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
			[]	[]	[]	[]	[]	[]	    队列
		   -------------------------
			rear

			front
		   -------------------------
			[1]	[]	[]	[]	[]	[]	    队列
		   -------------------------
				rear = 1

	ps: front != rear -> 肯定能够插入
		front == rear -> 是不是队列满了
	*/
	if (sq->front == sq->rear) return frontEQrearHandle(sq, data);		// 边界, 全满（front = rear && length= MaxSize ）或者全空(length = 0)；
	if (sq->front != sq->rear) return rearBorderHandle(sq, data);
	exit(0);
}

Rstatus staticQueueFrontPop(SQueue* sq)
{
	/*
			front
		   -------------------------
			[]	[]	[]	[]	[]	[]	    队列
		   -------------------------
			rear

			front
		   -------------------------
			[1]	[]	[]	[]	[]	[]	    队列
		   -------------------------
				rear = 1

	1. 空队列（sq->length = 0）
	2. 非空队列（sq->length != 0）

	*/
	if (!sq->length) 
	{
		printf("队列无元素! %zd %d", sq->length, MaxSize);
		exit(0);
	}
	// 判断 front 边界问题
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
