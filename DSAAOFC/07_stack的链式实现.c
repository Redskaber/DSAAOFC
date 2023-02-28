#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "07_stack����ʽʵ��.h"


/*
		slp -> [data|ptr] -> [] ->... -> [] -> NULL;
*/

Rstatus linkStackInit(LinkStack* linkstack)
{
	/*
		ͷָ��	-> ͷ��㣨���������� -> NULL;
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
	LinkStack* newElem =  createLinkStackElem(data);		// �µ�Ԫ�ؽ��
	LinkStack* headElem =  linkstack->next;					// ͷ���
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

	LinkStack* headElem = linkstack->next;					// ͷ���
	LinkStack* firstElem = headElem->next;			// ���ǵ�һ��ֵҲ���Ƴ���ֵ
	if (!firstElem) return NULL;					// stack Ϊ��ջʱ

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
