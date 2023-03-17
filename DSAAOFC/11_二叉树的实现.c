#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
#include "11_��������ʵ��.h"



static Lnode* createBinNode(ElemType data)
{
	Lnode* newNode = NULL;
	newNode = (Lnode*)malloc(sizeof(Lnode));
	assert(newNode != NULL);
	newNode->data = data;
	newNode->leftChild = NotChild;
	newNode->rightChild = NotChild;
	newNode->parent = NotParent;
	newNode->leftBor = NotBor;
	newNode->rightBor = NotBor;
	return newNode;
}

static bool isEmtryTree(LBinTree* lbtree)
{
	return lbtree->total == 0;
}

static void binTreeNodeDestroy(Lnode* node)
{
	if (node->leftChild != NotChild) binTreeNodeDestroy(node->leftChild);
	if (node->rightChild != NotChild) binTreeNodeDestroy(node->rightChild);
	free(node);
}

static Rstatus push(LBinTree* lbtree, ElemType data)
{
	/*
			A
		  B   C
		D  E F  G 
	*/
	Lnode* newNode = createBinNode(data);
	bool flag = isEmtryTree(lbtree);
	if (flag) lbtree->next =  lbtree->root = newNode;
	if (!flag)
	{
		// �ж�next��ӵ��ӽڵ��Ƿ��Ѿ�ȫ�����
		if (lbtree->next->leftChild == NotChild)
		{
			// �жϸ��ڵ���û���ֵܽڵ㣬���ֵܽڵ�˵����leftchildԪ��Ҳ��leftBor
			if (lbtree->next->leftBor != NotBor)
			{
				Lnode* leftBor = lbtree->next->leftBor;
				Lnode* leftBorChild = leftBor->rightChild;
				newNode->leftBor = leftBorChild;
				leftBorChild->rightBor = newNode;

			}

			// �ڵ�û���ӽڵ㣬��Ӳ�ִ��
			lbtree->next->leftChild = newNode;
			newNode->parent = lbtree->next;
		}
		else if (lbtree->next->rightChild == NotChild)
		{
			Lnode* leftnode;
			leftnode = lbtree->next->leftChild;
			lbtree->next->rightChild = newNode;
			newNode->parent = lbtree->next;
			newNode->leftBor = leftnode;
			leftnode->rightBor = newNode;	// ͬ���ֵ�

			// ����nextӦ���������1.���Ǳ߽磨�����ƶ���2.�߽�(��һ�㣬�����ƶ�)
			if (lbtree->next->parent != NotParent)
			{
				// lbtree->next ��һ���ǽ��������ӵ�, �ж� lbtree->next �Ƿ��Ǳ߽�
				if (lbtree->next->rightBor == NotBor)
				{
					lbtree->next = lbtree->next->leftChild;
					while (lbtree->next->leftBor != NotBor) lbtree->next = lbtree->next->leftBor;
				}
				else if (lbtree->next->rightBor != NotBor) lbtree->next = lbtree->next->rightBor;	// �Ǳ߽�Ľڵ��ƶ�
			}
			else if (lbtree->next->parent == NotParent)	lbtree->next = lbtree->next->leftChild;	// �ڶ���ĵڶ���Ԫ��
		}	
	}

	if ((lbtree->total) == (pow(2, lbtree->deep) - 1))
	{
		lbtree->deep = (int)log2(lbtree->total + 1) + 1; // deep = log2(total+1)		// ��ȸ���	
	}
	int nodeNumber = lbtree->total + 1;
	if (nodeNumber == 2) lbtree->leaf = 1;
	if (nodeNumber > 2 && nodeNumber % 2)
	{
		lbtree->degree++;
		lbtree->leaf = lbtree->degree + 1;
	}
	lbtree->nodeLis[lbtree->total] = newNode;		// case
	lbtree->total++;

	return true;
}

// �ݹ���������õݹ�Ҳ���ԣ�
static Rstatus preorderTraversal(LBinTree* lbtree)		// �������
{
	return _preorderTraversal(lbtree->root);
}

static Rstatus midorderTraversal(LBinTree* lbtree)		// �������
{
	return _midorderTraversal(lbtree->root);
}
	
static Rstatus postorderTraversal(LBinTree* lbtree)	// �������
{
	return _postorderTraversal(lbtree->root);
}

static Rstatus _preorderTraversal(Lnode* node)
{
	printf("%d ", node->data);
	if (node->leftChild != NotChild) _preorderTraversal(node->leftChild);
	if (node->rightChild != NotChild) _preorderTraversal(node->rightChild);
}

static Rstatus _midorderTraversal(Lnode* node)
{
	if (node->leftChild != NotChild) _midorderTraversal(node->leftChild);
	printf("%d ", node->data);
	if (node->rightChild != NotChild) _midorderTraversal(node->rightChild);
}

static Rstatus _postorderTraversal(Lnode* node)
{
	if (node->leftChild != NotChild) _postorderTraversal(node->leftChild);
	if (node->rightChild != NotChild) _postorderTraversal(node->rightChild);
	printf("%d ", node->data);
}

static Rstatus printNodeInfo(LBinTree* lbtree)
{
	Lnode* temp;
	Lnode* templd;
	Lnode* temprd;
	Lnode* templb;
	Lnode* temprb;
	for (int i = 0; i < lbtree->total; i++)
	{
		temp = lbtree->nodeLis[i]->parent;
		temp = (temp != NotParent) ? temp->data : 0;
		templd = lbtree->nodeLis[i]->leftChild;
		templd = (templd != NotChild) ? templd->data : 0;
		temprd = lbtree->nodeLis[i]->rightChild;
		temprd = (temprd != NotChild) ? temprd->data : 0;
		templb = lbtree->nodeLis[i]->leftBor;
		templb = (templb != NotBor) ? templb->data : 0;
		temprb = lbtree->nodeLis[i]->rightBor;
		temprb = (temprb != NotBor) ? temprb->data : 0;
		printf("data:%d, self:%d, parent:%d, leftChild:%d, rightChild:%d, leftBor:%d, rightBor:%d\n",
			lbtree->nodeLis[i]->data, lbtree->nodeLis[i]->data, temp,
			templd, temprd, 
			templb, temprb
		);
	}
	printf("\n");
	return true;
}

static Rstatus printBinTreeInfo(LBinTree* lbtree)
{
	printf("lbtree->total:%d, lbtree->deep:%d, lbtree->degree:%d, lbtree->leaf:%d\n",lbtree->total,lbtree->deep,lbtree->degree,lbtree->leaf);
	return true;
}

Rstatus BinTreeInit(LBinTree* lbtree)
{
	lbtree->root = NULL;
	lbtree->next = NULL;
	Lnode** nodelis = NULL;
	nodelis = (Lnode**)malloc(InitMomery * sizeof(Lnode*));
	assert(nodelis != NULL);
	lbtree->nodeLis = nodelis;		// case
	lbtree->deep = 0;
	lbtree->degree = 0;
	lbtree->leaf = 0;
	lbtree->total = 0;

	lbtree->push = push;
	lbtree->preorderTraversal = preorderTraversal;
	lbtree->midorderTraversal = midorderTraversal;
	lbtree->postorderTraversal = postorderTraversal;
	lbtree->isEmtryTree = isEmtryTree;
	lbtree->printNodeInfo = printNodeInfo;
	lbtree->printBinTreeInfo = printBinTreeInfo;

	return true;
}

Rstatus BinTreeDestroy(LBinTree* lbtree)
{
	binTreeNodeDestroy(lbtree->root);
	free(lbtree->nodeLis);		// case  ����ʹ��
	lbtree->root = NULL;
	lbtree->deep = 0;
	lbtree->degree = 0;
	lbtree->leaf = 0;
	lbtree->total = 0;
	return true;
}

