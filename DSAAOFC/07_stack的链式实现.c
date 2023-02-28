#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "07_stack的链式实现.h"


/*
		slp -> [data|ptr] -> [] ->... -> [] -> NULL;
*/

Rstatus linkStackInit(LinkStack* linkstack)
{
	/*
		头指针	-> 头结点（管理，辅助） -> NULL;
		linkstack
			- ELEM = NULL;
			- next = headElem;
	*/
	linkstack->data = NULL;
	linkstack->next = createLinkStackElem(0);
	return true;
}

LinkStack* createLinkStackElem(ElemType data)
{
	LinkStack* Elem = NULL;
	Elem = (LinkStack*)malloc(sizeof(LinkStack));
	assert(Elem != NULL);
	Elem->data = data;
	Elem->next = NULL;

	return Elem;
}

Rstatus destroyLinkStackElem(LinkStack* linkstack)
{
	free(linkstack);
	return true;
}

Rstatus linkStackPush(LinkStack* linkstack, ElemType data)
{
	/*
		slp->head -> NULL
		slp->head -> 1 -> NULL
		slp->head -> 2 -> 1 -> NULL
		slp->head -> 3 -> 2 -> 1 -> NULL
	*/
	LinkStack* newElem =  createLinkStackElem(data);		// 新的元素结点
	LinkStack* headElem =  linkstack->next;					// 头结点
	if (headElem->next)
	{
		LinkStack* afterElem = headElem->next;
		newElem->next = afterElem;
	}
	headElem->next = newElem;
	return true;
}

Rstatus linkStackPop(LinkStack* linkstack)
{
	/*
		slp->head -> 3 -> 2 -> 1 -> NULL
		slp->head -> 2 -> 1 -> NULL
		slp->head -> 1 -> NULL
		slp->head -> NULL
	*/

	LinkStack* headElem = linkstack->next;					// 头结点
	LinkStack* firstElem = headElem->next;			// 既是第一个值也是移除的值
	if (!firstElem) return NULL;					// stack 为空栈时

	LinkStack* afterElem = firstElem->next;  
	headElem->next = afterElem;
	destroyLinkStackElem(firstElem);
	return true;
}

Rstatus linkStackPrint(LinkStack* linkstack)
{
	LinkStack* temp = linkstack->next;		// head
	if (temp->next == NULL) return NULL;

	temp = temp->next;	// first
	while (temp)
	{
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}
