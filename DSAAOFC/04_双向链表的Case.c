/*
	测试 双向链表
		- 双向链表结点管理	struct
			- 头结点
			- 尾节点
			- 链长
		- 双向链表结点		struct
			- 值域
			- 指针域{ 前指针， 后指针 }

*/
#include<stdio.h>
#include<stdlib.h>
#include"04_双向链表的构建.h"



int start_bidirectional_linker()
{
	BiDLinker bdlp;
	BidLinkerInit(&bdlp);
	BidLinkPrint(&bdlp);
	BNode* a =  createBNode(100);
	BNode* b =  createBNode(200);
	BNode* c =  createBNode(300);
	BNode* d =  createBNode(400);
	BNode* e =  createBNode(100);
	BNode* f =  createBNode(200);
	BNode* g =  createBNode(300);
	BNode* h =  createBNode(1000);
	BNode* i =  createBNode(1100);
	BNode* j =  createBNode(1200);
	BNode* k =  createBNode(1300);
	BNode* l =  createBNode(1400);
	BNode* r1 =  createBNode(2000);
	BNode* r2 =  createBNode(2000);
	BNode* r3 =  createBNode(2000);
	BNode* r4 =  createBNode(2000);
	_addBNode(&bdlp, a);
	_addBNode(&bdlp, b);
	_addBNode(&bdlp, c);
	_addBNode(&bdlp, d);
	printf("%d %d %zd %p\n", bdlp.headNode->data,bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	// _appendBNode(&bdlp, a);		// error  bdlp-> a[] -> b[] -> c[]... -> end[]-> [bdlp->a[]];  loop circle
	_appendBNode(&bdlp, e);
	_appendBNode(&bdlp, f);
	_appendBNode(&bdlp, g);
	_appendBNode(&bdlp, h);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	_insertBNode(&bdlp, a, i);
	_insertBNode(&bdlp, b, j);
	_insertBNode(&bdlp, c, k);
	_insertBNode(&bdlp, d, l);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	_replaceBNode(&bdlp, a, r1);
	_replaceBNode(&bdlp, b, r2);
	_replaceBNode(&bdlp, c, r3);
	_replaceBNode(&bdlp, d, r4);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	_removeBNode(&bdlp, a);		// data == data
	_removeBNode(&bdlp, b);
	_removeBNode(&bdlp, k);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	_frontRemoveBNode(&bdlp);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	_popBNode(&bdlp);
	BidLinkPrint(&bdlp);
	printf("%d %d %zd %p\n", bdlp.headNode->data, bdlp.endNode->data, bdlp.length, bdlp.endNode->afterNode);

	return 0;
}