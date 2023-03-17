#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "10_��������ʵ��.h"



/*
	��������ʵ��
		- �ڵ�ʵ��
		- ����ڵ�ʵ��
*/


static Rstatus destroyBinaryTree(arrBinTree* abtree);
static Rstatus push(arrBinTree* abtree, ElemType data);
static Rstatus printBTree(arrBinTree* abtree, ergodicType code);
static BTNode* proRcursion(arrBinTree* abtree, BTNode* node, int flag, int leaf);
static Index getNodeParentIndex(Index nodeInd);
Rstatus proPrintBTree(arrBinTree* abtree);



BTNode* createBTNode(ElemType data)
{
	BTNode* newNode = NULL;
	newNode = (BTNode*)malloc(sizeof(BTNode));
	assert(newNode != NULL);
	newNode->data = data;
	newNode->leftChild = NotChildInd;
	newNode->rightChild = NotChildInd;
	newNode->selfInd = NULL;

	return newNode;
}


Rstatus destroyBTNode(BTNode* destNode)
{
	free(destNode);
	destNode = NULL;
	return true;
}



Rstatus binaryTreeInit(arrBinTree* abtree)
{
	/*
		�������ĳ�ʼ����
			- array ����ռ�
			�����ʼ��
	*/
	BTNode* *array = NULL;
	array = (BTNode**)malloc(initArrayMem * sizeof(BTNode*));
	assert(array != NULL);
	abtree->array=array;
	abtree->total = 0;
	abtree->deep = 0;
	abtree->leaf = 0;
	abtree->degree = 0;
	abtree->capacity = initArrayMem;

	abtree->createBTNode = createBTNode;
	abtree->destroyBTNode = destroyBTNode;
	abtree->push = push;
	abtree->printBTree = printBTree;
	abtree->proPrintBTree = proPrintBTree;
	abtree->destroyBinaryTree = destroyBinaryTree;

	return true;
}


Rstatus destroyBinaryTree(arrBinTree* abtree)
{
	for (int i = 0; i < abtree->total; i++)
	{
		destroyBTNode(abtree->array[i]);
	}

	free(abtree->array);
	abtree->total = 0;
	abtree->deep = 0;
	abtree->leaf = 0;
	abtree->degree = 0;
	abtree->capacity = 0;
	return true;
}


Index getNodeParentIndex(Index nodeInd)
{
	return (int)((nodeInd + 1) / 2) - 1;		// ��ȡ���ڵ�����λ��
}


Rstatus push(arrBinTree* abtree, ElemType data)
{
	BTNode *newNode = createBTNode(data);
	newNode->selfInd = abtree->total;
	abtree->array[abtree->total] = newNode;
	
	int nodeNumber = abtree->total + 1;

	if (abtree->total)
	{
		int parentInd = getNodeParentIndex(abtree->total);		// ��ȡ���ڵ�����λ��
		if (nodeNumber % 2 == 0) abtree->array[parentInd]->leftChild = abtree->total;		// ����
		if (nodeNumber % 2 ) abtree->array[parentInd]->rightChild = abtree->total;			// �Һ���
	}
	if ((abtree->total) == (pow(2,abtree->deep)-1))
	{
		abtree->deep = (int)log2(abtree->total + 1) + 1; // deep = log2(total+1)		// ��ȸ���	
	}

	if (nodeNumber == 2) abtree->leaf = 1;
	if (nodeNumber > 2 && nodeNumber % 2)
	{
		abtree->degree++;
		abtree->leaf = abtree->degree + 1;
	}
	abtree->total++;

	return abtree->total -1;
}

BTNode* proRcursion(arrBinTree* abtree, BTNode* node, int flag, int leaf)
{
	/*
	* int flag: ���Ʊ�������
	* int leaf: ���ƽ���ʱ��
	* 1.��ȵݹ�
	* 2.Ҷ�Ӵ���
	*/

	if (node->leftChild != NotChildInd && flag == NextleftChild)		// ���ӵݹ飨��ȣ�
	{
		node = abtree->array[node->leftChild];
		printf("%d ", node->data);
		return proRcursion(abtree, node, flag, leaf);
	}

	if (node->leftChild == NotChildInd && node->rightChild == NotChildInd)	// ��Ҷ�Ӵ���
	{
		leaf++;	
		flag = NextrightChild;
		int parentInd = getNodeParentIndex(node->selfInd);		
		node = abtree->array[parentInd];
		return proRcursion(abtree, node, flag, leaf);

	}

	if (node->rightChild == NotChildInd && flag == NextrightChild)			// ��Ҷ�Ӵ���
	{
		if (node->selfInd == 0)
		{
			printf("�������������\n");
			return NULL;
		}
		int parentInd;

		if (node->leftChild != NotChildInd && abtree ->deep > 3)		// ����ȴ���3��ʱ���Ż����
		{
			parentInd = getNodeParentIndex(node->selfInd);
			parentInd = getNodeParentIndex(parentInd);
			node = abtree->array[parentInd];
			return proRcursion(abtree, node, flag, leaf);
		}
		parentInd = getNodeParentIndex(node->selfInd);
		node = abtree->array[parentInd];
		return proRcursion(abtree, node, flag, leaf);
	}

	if (node->rightChild != NotChildInd && flag == NextrightChild)
	{
		flag = NextleftChild;
		node = abtree->array[node->rightChild];
		printf("%d ", node->data);
		if (node->leftChild == NotChildInd && node->rightChild == NotChildInd)	// ��Ҷ�Ӵ���
		{
			// �жϽ����ݹ�����(leaf)
			leaf++;
			flag = NextrightChild;
			if (leaf == abtree->leaf)
			{
				printf("�������������\n");
				return NULL;
			}

			int parentInd;
			int grandInd;
			parentInd = getNodeParentIndex(node->selfInd);		// ��ȡ���ڵ�����λ��
			grandInd = getNodeParentIndex(parentInd);			// ��ȡ��ڵ�����λ��
			BTNode*  grand = abtree->array[grandInd];

			if (parentInd == grand->leftChild)		// ���Ӵ�������Ѿ��ݹ��꣬��ʼ�����Һ��ӣ�
			{
				node = abtree->array[grandInd];		// ��ڵ�
				return proRcursion(abtree, node, flag, leaf);
			}
			if (parentInd == grand->rightChild)		// �Һ��Ӵ����Һ��Ӵ�����������������ѽ�������ɣ�������ڵ��ж����������Ǳߵĺ��ӣ�
			{
				int tempInd;
				tempInd = grandInd;
				grandInd = getNodeParentIndex(grandInd);		// ��ȡ��ڵ�����λ��
				node = abtree->array[grandInd];					// ��ڵ�
				while (tempInd == node->leftChild && node->leftChild != 1)	 // leftChild����1,�������ڵ�������Ѿ�ȫ���ݹ���ɣ��õ�����
				{
					tempInd = grandInd;
					grandInd = getNodeParentIndex(grandInd);		// ��ȡ��ڵ�����λ��
					node = abtree->array[grandInd];					// ��ڵ�
				}
				return proRcursion(abtree, node, flag, leaf);
			}
		}
		return proRcursion(abtree, node, flag, leaf);
	}
}


BTNode* midRcursion(arrBinTree* abtree, BTNode* node, int flag, int leaf){}

Rstatus proPrintBTree(arrBinTree* abtree)
{
	/*
		 A
		B C   => ABC
	*/
	BTNode* node = abtree->array[0];
	printf("%d ", node->data);
	proRcursion(abtree, node, NextleftChild, StartTempLeaf);		// �ײ��ڵ�
	return true;
}

Rstatus midPrintBTree(arrBinTree* abtree)
{
	/*
		 A
		B C   => BAC
	*/
	BTNode* node = abtree->array[0];
	midRcursion(abtree, node, NextleftChild, StartTempLeaf);		// �ײ��ڵ�
}

Rstatus aftPrintBTree(arrBinTree* abtree)
{
	/*
		 A
		B C   => BCA
	*/
	BTNode* node = abtree->array[0];
}



Rstatus printBTree(arrBinTree* abtree, ergodicType code)
{
	/*
		ergodicType: ����������
			- pro	1		[������]
			- mid	2		[�����]
			- aft	3		[���Ҹ�]
	*/
	if (abtree->total == 0) return NULL;
	if (code == pro) return proPrintBTree(abtree);
	if (code == mid) return midPrintBTree(abtree);
	if (code == aft) return aftPrintBTree(abtree);
	return false;
}


void printBTreeInfo(arrBinTree* abtree)
{
	printf("\nabtree.total:%d, abtree.deep:%d, abtree.degree:%d, abtree.leaf:%d, abtree.capacity:%d\n",
		abtree->total, abtree->deep, abtree->degree, abtree->leaf, abtree->capacity);
}