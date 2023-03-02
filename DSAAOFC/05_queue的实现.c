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
				- front 移除位置边界问题	(front == MaxSize -1) >  (sq->front == MaxSize - 1) ? (sq->front = 0) : (sq->front++);
	
			3.rear == front {全满，全空}	-> length(实际有效个数)
*/


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
	*/
	if (sq->length == MaxSize)		// 边界, 上溢出
	{
		printf("队列已满！%zd = %d\n", sq->length, MaxSize);
		exit(0);
	}
	sq->queue[sq->rear] = data;
	sq->length++;
	(sq->rear == MaxSize - 1) ? (sq->rear = 0) : (sq->rear++); // 判断 rear 边界问题

	return true;
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
	if (!sq->length)	// 下溢出
	{
		printf("队列无元素! %zd %d", sq->length, MaxSize);
		exit(0);
	}
	
	sq->queue[sq->front] = InitMark;
	sq->length--;
	(sq->front == MaxSize - 1) ? (sq->front = 0) : (sq->front++);	// 判断 front 边界问题
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
