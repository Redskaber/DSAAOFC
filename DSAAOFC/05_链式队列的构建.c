#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "05_链式队列的构建.h"

static QueueElem CreateQueueNode(ElemType data);
static Rstatus DestroyQueueNode(QueueElem node);
static Rstatus _LinkQueueRearPush(LinkQueue* lq, QueueElem node);


QueueElem CreateQueueNode(ElemType data)
{
	QueueElem newElem = NULL;
	newElem = (QueueElem)malloc(sizeof(QueueNode));
	assert(newElem != NULL);
	memset(newElem, 0, sizeof(QueueNode));
	newElem->data = data;
	newElem->next = NULL;
	return newElem;
}

Rstatus DestroyQueueNode(QueueElem node) 
{
	free(node);
	node = NULL;
	return true;
}


Rstatus LinkQueueInit(LinkQueue* lq)
{
	QueueElem headNode = CreateQueueNode(0);
	lq->headNode = lq->endNode = headNode;
	return true;
}

Rstatus LinkQueueFrontPush(LinkQueue* lq, ElemType data)
{
	QueueElem newNode = CreateQueueNode(data);
	return _LinkQueueRearPush(lq, newNode);
}

Rstatus _LinkQueueRearPush(LinkQueue* lq, QueueElem node)
{
	QueueElem endNode = lq->endNode;
	(endNode) ? (endNode->next = node) : (lq->endNode = node);
	lq->endNode = node;
	return true;
}

Rstatus LinkQueueFrontPop(LinkQueue* lq)
{
	QueueElem headNode = lq->headNode;
	QueueElem popNode = headNode->next;
	if (popNode == NULL) 
	{
		printf("链式队列已空!");
		exit(0);
	}
	QueueElem afterNode = popNode->next;
	headNode->next = afterNode;
	DestroyQueueNode(popNode);
	return true;
}


Rstatus LinkQueuePrint(LinkQueue* lq)
{
	QueueElem temp = lq->headNode->next;
	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
