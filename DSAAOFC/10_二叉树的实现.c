#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "10_二叉树的实现.h"



/*
	二叉树的实现
		- 节点实现
		- 管理节点实现
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
		二叉树的初始化：
			- array 分配空间
			其余初始化
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
	return (int)((nodeInd + 1) / 2) - 1;		// 获取父节点索引位置
}


Rstatus push(arrBinTree* abtree, ElemType data)
{
	BTNode *newNode = createBTNode(data);
	newNode->selfInd = abtree->total;
	abtree->array[abtree->total] = newNode;
	
	int nodeNumber = abtree->total + 1;

	if (abtree->total)
	{
		int parentInd = getNodeParentIndex(abtree->total);		// 获取父节点索引位置
		if (nodeNumber % 2 == 0) abtree->array[parentInd]->leftChild = abtree->total;		// 左孩子
		if (nodeNumber % 2 ) abtree->array[parentInd]->rightChild = abtree->total;			// 右孩子
	}
	if ((abtree->total) == (pow(2,abtree->deep)-1))
	{
		abtree->deep = (int)log2(abtree->total + 1) + 1; // deep = log2(total+1)		// 深度更新	
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
	* int flag: 控制遍历方向
	* int leaf: 控制结束时机
	* 1.深度递归
	* 2.叶子处理
	*/

	if (node->leftChild != NotChildInd && flag == NextleftChild)		// 左孩子递归（深度）
	{
		node = abtree->array[node->leftChild];
		printf("%d ", node->data);
		return proRcursion(abtree, node, flag, leaf);
	}

	if (node->leftChild == NotChildInd && node->rightChild == NotChildInd)	// 左叶子处理
	{
		leaf++;	
		flag = NextrightChild;
		int parentInd = getNodeParentIndex(node->selfInd);		
		node = abtree->array[parentInd];
		return proRcursion(abtree, node, flag, leaf);

	}

	if (node->rightChild == NotChildInd && flag == NextrightChild)			// 右叶子处理
	{
		if (node->selfInd == 0)
		{
			printf("先序遍历结束！\n");
			return NULL;
		}
		int parentInd;

		if (node->leftChild != NotChildInd && abtree ->deep > 3)		// 当深度大于3层时，才会出现
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
		if (node->leftChild == NotChildInd && node->rightChild == NotChildInd)	// 右叶子处理
		{
			// 判断结束递归条件(leaf)
			leaf++;
			flag = NextrightChild;
			if (leaf == abtree->leaf)
			{
				printf("先序遍历结束！\n");
				return NULL;
			}

			int parentInd;
			int grandInd;
			parentInd = getNodeParentIndex(node->selfInd);		// 获取父节点索引位置
			grandInd = getNodeParentIndex(parentInd);			// 获取祖节点索引位置
			BTNode*  grand = abtree->array[grandInd];

			if (parentInd == grand->leftChild)		// 左孩子处理（左边已经递归完，开始进行右孩子）
			{
				node = abtree->array[grandInd];		// 祖节点
				return proRcursion(abtree, node, flag, leaf);
			}
			if (parentInd == grand->rightChild)		// 右孩子处理（右孩子处理完表明，此子树已近处理完成，跳到祖节点判断他父辈是那边的孩子）
			{
				int tempInd;
				tempInd = grandInd;
				grandInd = getNodeParentIndex(grandInd);		// 获取祖节点索引位置
				node = abtree->array[grandInd];					// 祖节点
				while (tempInd == node->leftChild && node->leftChild != 1)	 // leftChild等于1,表明根节点的左树已经全部递归完成，该到右树
				{
					tempInd = grandInd;
					grandInd = getNodeParentIndex(grandInd);		// 获取祖节点索引位置
					node = abtree->array[grandInd];					// 祖节点
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
	proRcursion(abtree, node, NextleftChild, StartTempLeaf);		// 底部节点
	return true;
}

Rstatus midPrintBTree(arrBinTree* abtree)
{
	/*
		 A
		B C   => BAC
	*/
	BTNode* node = abtree->array[0];
	midRcursion(abtree, node, NextleftChild, StartTempLeaf);		// 底部节点
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
		ergodicType: 遍历的类型
			- pro	1		[根左右]
			- mid	2		[左根右]
			- aft	3		[左右根]
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