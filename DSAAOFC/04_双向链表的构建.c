#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "04_双向链表的构建.h"



/*
	实现双向链表
		- 双向链表结点管理
			- 初始化
		- 双向链表结点
			- 初始化

*/


BNode* createBNode(ElemType data)
{
	/*
		BNode [perNode|data|afterNode]
	
	start:
		data = 0;
		perNode = NULL;
		afterNode = NULL;
	*/
	BNode* bnode = NULL;
	bnode = (BNode*)malloc(sizeof(BNode));
	assert(bnode != NULL);
	memset(bnode, 0, sizeof(BNode));
	bnode->data = data;
	bnode->perNode = NULL;
	bnode->afterNode = NULL;

	return bnode;
}

Rstatus destroyBNode(BNode* node) 
{
	/*
		malloc -> free
	*/

	free(node);
	node = NULL;
	return 1;
}


Rstatus BidLinkerInit(BiDLinker* bdlp)
{
	/*
		bdlp-> headNode -> [||] <- endNode
			- headNode
			- endNode
			- length
	
	 start:
		headNode = endNode = malloc
		length = 0
	
	*/
	BNode* headNode =  createBNode(0);
	bdlp->headNode = bdlp->endNode = headNode;
	bdlp->length = 0;

	return 1;
}

Rstatus BidLinkPrint(BiDLinker* bdlp)
{
	if (bdlp->length == 0) return NULL;
	BNode* temp = bdlp->headNode->afterNode;

	do
	{
		printf("%d ",temp->data);
		temp = temp->afterNode;
	} while (temp);
	printf("\n");

	return bdlp->length;
}

BNode* addBNode(BiDLinker* bdlp, ElemType data)
{
	return _addBNode(bdlp, createBNode(data));
}

BNode* appendBNode(BiDLinker* bdlp, ElemType data)
{
	return _appendBNode(bdlp, createBNode(data));
}

BNode* insertBNode(BiDLinker* bdlp, ElemType afterData, ElemType data)
{
	BNode* temp = createBNode(afterData);
	BNode* afternode =  _findBNode(bdlp, afterData);
	assert(afternode != NULL);
	BNode* NewNode = _insertBNode(bdlp, afternode, createBNode(data));
	assert(NewNode != NULL);
	destroyBNode(temp);
	return NewNode;
}

BNode* removeBNode(BiDLinker* bdlp, ElemType data)
{
	BNode* temp = createBNode(data);
	BNode* reNode = _removeBNode(bdlp, temp);
	destroyBNode(temp);
	return reNode;
}

BNode* frontRemoveBNode(BiDLinker* bdlp)
{
	return _frontRemoveBNode(bdlp);
}

BNode* popBNode(BiDLinker* bdlp)
{
	return _popBNode(bdlp);
}

BNode* replaceBNode(BiDLinker* bdlp, ElemType reData, ElemType data)
{
	BNode* reNode = createBNode(reData);
	BNode* renode = _findBNode(bdlp, reNode);
	destroyBNode(reNode);
	if (renode == NULL) return NULL;

	return _replaceBNode(bdlp,renode, createBNode(data));
}

BNode* findBNode(BiDLinker* bdlp, ElemType data)
{
	BNode* temp = createBNode(data);
	BNode* fnode = _findBNode(bdlp, temp);
	destroyBNode(temp);
	return fnode;
}

BNode* _addBNode(BiDLinker* bdlp, BNode* node)
{
	/*
		bdlp-> headNode -> [||] -> [||] -> ... -> endNode[||]
		bdlp-> headNode -> node -> [||] -> [||] -> ... -> endNode[||]

		bdlp-> headNode <per - after> [||]node <per - after> temp[||]...

	*/

	if (bdlp->length == 0) return _appendBNode(bdlp, node);

	BNode* temp =  bdlp->headNode->afterNode;

	bdlp->headNode->afterNode = node;
	node->perNode = bdlp->headNode;

	node->afterNode = temp;
	temp->perNode = node;

	bdlp->length++;
	return node;
}

BNode* _appendBNode(BiDLinker* bdlp, BNode* node)
{
	/*
		bdlp-> headNode -> [||] -> [||] -> ... -> endNode[||]
		bdlp-> headNode -> [||] -> [||] -> ... -> e [||] -> node[end];

		bdlp-> headNode <per - after> [||]node
		bdlp-> headNode ...-> end[||] <per - after> node
	*/

	if (bdlp->length == 0)
	{
		bdlp->headNode->afterNode = node;
		node->perNode = bdlp->headNode;
	}
	if (bdlp->length != 0)
	{
		bdlp->endNode->afterNode = node;
		node->perNode = bdlp->endNode;
	}
	bdlp->endNode = node;
	bdlp->length++;
	
	return node;
}

BNode* _insertBNode(BiDLinker* bdlp, BNode* afterNode, BNode* node)
{
	/*
		bdlp-> headNode -> [||] -> afterNode[||] -> ... -> endNode[||]
			node
		bdlp-> headNode -> temp[||] <per - after> node <per - after> afterNode[||] ->... -> endNode[||]

	*/
	BNode* afternode = _findBNode(bdlp, afterNode);
	assert(afternode != NULL);

	if (bdlp->length == 0) return _appendBNode(bdlp, node);			// end
	if (afternode == bdlp->headNode) return _addBNode(bdlp, node);	// head

	// body ->node->afterNode
	BNode* temp = afternode->perNode;

	afternode->perNode = node;		// 后
	node->afterNode = afternode;

	temp->afterNode = node;			// 前
	node->perNode = temp;

	bdlp->length++;

	return node;
}

BNode* _removeBNode(BiDLinker* bdlp, BNode* reNode)
{
	/*
		bdlp-> headNode -> [||] <per - after> reNode[||] <per - after> ... -> endNode[||]
		if reNode[||] in 
		
		ps: free(reNode)

	*/
	BNode* renode = _findBNode(bdlp, reNode);
	if (renode == NULL) return NULL;
	
	if (bdlp->length == 1) return _frontRemoveBNode(bdlp);		// head
	if (renode == bdlp->endNode) return _popBNode(bdlp);		// end

	// body
	BNode* per = renode->perNode;
	BNode* after = renode->afterNode;

	per->afterNode = after;		// remove的前面指向remove的后面
	after->perNode = per;		// remove的后面指向remove的前面

	bdlp->length--;

	return renode;
}

BNode* _frontRemoveBNode(BiDLinker* bdlp)
{
	/*
		bdlp-> headNode <per - after> [||]<per  - after> [||] ... -> endNode[||]
	*/
	if (bdlp->length == 0) return NULL;

	BNode* reNode = bdlp->headNode->afterNode;

	if (bdlp->length == 1)		// len == 1
	{
		bdlp->headNode->afterNode = NULL;
		bdlp->endNode = NULL;
		bdlp->length = 0;
		return reNode;
	}

	BNode* after = reNode->afterNode;
	bdlp->headNode->afterNode = after;
	after->perNode = bdlp->headNode;
	bdlp->length--;
	return reNode;
}

BNode* _popBNode(BiDLinker* bdlp)
{
	/*
		bdlp-> headNode <per - after> [||]<per  - after> [||] ... -> endNode[||]
	*/

	if (bdlp->length == 0) return NULL;

	BNode* reNode = bdlp->endNode;
	if (bdlp->length == 1)		// len == 1
	{
		bdlp->headNode->afterNode = NULL;
		bdlp->endNode = NULL;
		bdlp->length = 0;
		return reNode;
	}

	BNode* perNode = reNode->perNode;	// 移除的前一个
	bdlp->endNode = perNode;
	perNode->afterNode = NULL;
	bdlp->length--;
	
	return reNode;
}

BNode* _replaceBNode(BiDLinker* bdlp, BNode* reNode, BNode* node)
{
	/*
		bdlp-> headNode -> [||] -> [||] -> ... -> endNode[||]
		node[||]
		find
		replace
	*/
	BNode* fnode = _findBNode(bdlp, reNode);
	if (fnode == NULL) return NULL;

	BNode* pernode = fnode->perNode;
	BNode* afternode = fnode->afterNode;

	pernode->afterNode = node;
	node->perNode = pernode;

	node->afterNode = afternode;
	afternode->perNode = node;

	return node;
}

BNode* _findBNode(BiDLinker* bdlp, BNode* node)
{
	/*
		bdlp-> headNode -> [||] -> [||] -> ... -> endNode[||]
			? in  node
		return:
			- tempnode
			- NULL;
	*/
	if (bdlp->length == 0) return NULL;
	BNode* tempNode = bdlp->headNode->afterNode;
	do
	{
		if (node->data == tempNode->data)return tempNode;
		tempNode = tempNode->afterNode;
	} while (tempNode);

	return NULL;
}
