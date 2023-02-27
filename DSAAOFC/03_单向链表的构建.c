#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "03_单向链表的构建.h"


/*
	创建一个单链表的节点（结点）
	SingleNode
		- data
		- next

	- 头指针	headp		指向头节点的指针，用以标识链表。
	- 头节点    head		用于辅助整体链表操作功能的结点，可选
	- 元首结点	firstnode	第一个存储 有效数据的结点。

	单链表管理结构
	SingleLinker
		- firstnode
		- endnode
		- length

	- 链表的元首结点
	- 链表的结尾结点
	- 链表的长度(有效结点个数)	除头节点

	c4133 ->强制类型转化（解决）
*/

void SingleLinkerInit(SingleLinker* slp)
{
	/*
	slp 表示的是一个链表指针

		slp->firstNode: 链表的元首结点
		slp->endNode:	链表的结尾结点
		slp->length;:	链表的长度(有效结点个数)	除头节点

		SingleLinker* slp (头指针) -> [ | ] (头结点) -> NULL

		slp -> headp -> NULL
		- free(slp->firstnode) == free(headp)

		slp -> { headNode		-> headp
			   { endnode		-> headp
	*/
	// 管理linker，初始化时,头结点 == 尾结点
	SingleNode* Headp = createNode(0);;	// 有助于理解，这个是一个头结点
	slp->headNode = slp->endNode = Headp;
	slp->length = 0;
}

NodeCount SinLinNodePrint(SingleLinker* slp)
{
	SingleNode* beforeNode = slp->headNode->next;
	if (beforeNode != NULL)
	{
		do
		{
			printf("%d ", beforeNode->data);
			beforeNode = beforeNode->next;
		} while (beforeNode);
		printf("\n");
	}
	return (NodeCount)slp->length;
}

void SingleLinkerDestroy(SingleLinker* slp)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
		first->end
		headp
		slp
	*/

	SingleNode* nowNode = slp->headNode->next;
	slp->headNode->next = NULL;

	SingleNode* temp = nowNode;
	while (slp->length)		// first - end
	{
		temp = nowNode->next;
		destroyNode(nowNode);
		nowNode = temp;
		slp->length--;
	}
	free(slp->headNode);
}

Rstatus SingleLinkerIsEmrty(SingleLinker* slp)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
	*/
	if (slp->length == 0) return 1;
	SingleNode* temp = slp->headNode->next;

	while (temp->next)
	{
		if (temp->data != NULL) return 0;
		temp = temp->next;
	}
	return 1;
}



SingleNode* createNode(ElemType data)
{
	/*
		node
			- data	INIT
			- next  NULL
	*/
	SingleNode* sNode = NULL;
	sNode = (SingleNode*)malloc(sizeof(SingleNode));
	assert(sNode != NULL);
	memset(sNode, NODE_MARK, sizeof(SingleNode));
	sNode->data = data;
	sNode->next = NULL;
	
	return sNode;
}

void destroyNode(SingleNode* node)
{
	/*
		销毁掉结点释放内存
		- free(node)
		node = NULL;

	*/
	free(node);
	node = NULL;
}



SingleNode* addNode(SingleLinker* slp, ElemType data)
{
	/*
		createNode + addNode
	*/
	return _addNode(slp, createNode(data));
}

SingleNode* appendNode(SingleLinker* slp, ElemType data)
{
	return _appendNode(slp, createNode(data));
}

SingleNode* findNode(SingleLinker* slp, ElemType data)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
		finddata
		-> createNode -> findNode -> _findNode(findNode) -> free();
		return _findNode();
	*/
	SingleNode* tempNode  = createNode(data);
	SingleNode* findnode  = _findNode(slp,tempNode);
	destroyNode(tempNode);
	return findnode;
}

SingleNode* insertNode(SingleLinker* slp, ElemType perdata, ElemType data)
{
	
	return _insertNode(slp, findNode(slp, perdata), createNode(data));
}

SingleNode* removeNode(SingleLinker* slp, ElemType data)
{
	
	return _removeNode(slp, findNode(slp,data));

}

SingleNode* rfrontNode(SingleLinker* slp)
{
	/*
	slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
		first[|]
		t = first[|].next
		 headp[].next = t
		 slp.length--;

	return :
		- frontNode
		- NULL
	*/
	if (slp->length == 0) return NULL;
	SingleNode* frontNode = slp->headNode->next;
	SingleNode* afterNode = frontNode->next;
	slp->headNode->next = afterNode;
	if (slp->length == 1) slp->endNode = afterNode;
	slp->length--;
	return frontNode;
}

SingleNode* popNode(SingleLinker* slp)
{
	/*
	slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
		slp->endNode = perNode
		slp->length--
	*/
	if (slp->length == 0) return NULL;
	SingleNode* endNode = slp->endNode;
	SingleNode* perNode = _findperNode(slp, endNode);
	
	assert(perNode != NULL);

	perNode->next = NULL;
	slp->endNode = perNode;
	slp->length--;

	return endNode;
}

Rstatus replaceNodeVal(SingleLinker* slp, ElemType Repdata, ElemType data) 
{
	SingleNode* repNode = createNode(Repdata);
	Rstatus status =  _replaceNodeVal(slp, repNode, data);
	destroyNode(repNode);
	return; status;
}



SingleNode* _findNode(SingleLinker* slp, SingleNode* findNode)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
			findNode[|]
			while findNode in ...[|]
			return findNode
			if findNode == headNode;
			if findNode == endNode; 
		return:
			- linkNode
			- NULL		n'in
	*/
	if (findNode == NULL) return NULL;
	SingleNode* linkNode = slp->headNode;
	do
	{
		if (findNode->data == linkNode->data) return linkNode;
		linkNode = linkNode->next;

	} while (linkNode);
	return NULL;
}

SingleNode* _findperNode(SingleLinker* slp, SingleNode* findNode)
{
	if (findNode == NULL) return NULL;
	SingleNode* linkNode = slp->headNode->next;

	if (findNode == linkNode) return slp->headNode;	// first

	while (linkNode->next != findNode)		// body end
	{
		linkNode = linkNode->next;
	}
	if (linkNode->next == findNode) return linkNode;
	return NULL;
}

SingleNode* _addNode(SingleLinker* slp, SingleNode* NewNode)
{
	/*
		头添加结点
		slp -> headp -> node ...
						NewNode
		slp->length++;
		singlenode* afterNode
		slp->beforenode = Newnode
		newnode->next = afternode
	*/
	if (slp->length == 0) return _appendNode(slp, NewNode);

	SingleNode* firstNode = slp->headNode->next;
	slp->headNode->next = NewNode;
	NewNode->next = firstNode;
	slp->length++;

	return  NewNode;
}

SingleNode* _appendNode(SingleLinker* slp, SingleNode* NewNode)
{
	/*
		尾部添加node
		slp -> headp -> node ...->node
									  .next = NewNode
	*/			
	(slp->length == 0) ? (slp->headNode->next = NewNode) : (slp->endNode->next = NewNode);	// 将NewNode 添加到 单向链表表尾中
	slp->endNode = NewNode;				// 更新管理链表中的末尾结点
	slp->length++;						// 更新管理链表中的有效结点数
	return NewNode;
}

SingleNode* _insertNode(SingleLinker* slp, SingleNode* PerNode, SingleNode* NewNode)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
			
			NewNode[|]
			... -> PerNode[|] -> NewNode[|] -> ...
	*/
	SingleNode* perNode = _findNode(slp, PerNode);
	assert(perNode != NULL);
	if (perNode == slp->endNode) return _appendNode(slp, NewNode);
	if (perNode == slp->headNode) return _addNode(slp, NewNode);

	SingleNode* afterNode = perNode->next;
	perNode->next = NewNode;
	NewNode->next = afterNode;
	slp->length++;

	return NewNode;
}

SingleNode* _removeNode(SingleLinker* slp, SingleNode* removeNode)
{
	/*
	slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]

		data -> find(data) -> remove -> return re data
	*/
	SingleNode* removenode = _findNode(slp, removeNode);
	if (removenode == NULL) return NULL;

	if (removenode->next == NULL) return popNode(slp);	// endNode
	if (removenode == slp->headNode->next)	return rfrontNode(slp);// firstNode

	SingleNode* perLinkNode = _findperNode(slp, removenode);
	assert(perLinkNode != NULL);

	SingleNode* afterNode = removenode->next;
	perLinkNode->next = afterNode;
	slp->length--;

	return removenode;
}

Rstatus _replaceNodeVal(SingleLinker* slp, SingleNode* RepNode, ElemType data)
{
	/*
		slp -> headp[] ->first[|] -> two[|] -> ...-> end[|]
		find(repNode) -> .data = data
	*/
	SingleNode* repNode = _findNode(slp, RepNode);
	if (repNode == NULL) return NULL;
	repNode->data = data;
	return 1;
}

