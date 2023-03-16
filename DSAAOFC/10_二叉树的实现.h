#pragma once

#ifndef __10_BINARY_TREE_REALIZE_H__
	#define __10_BINARY_TREE_REALIZE_H__
	
	/*
		使用顺序表为基准的二叉树 *
		使用链表为基准的二叉树
	*/

#define INIT	


	typedef int Rstatus;
	typedef int Index;
	typedef int ergodicType;
	#define initArrayMem 50
	#define NotChildInd  -1
	#define NextleftChild  1
	#define NextrightChild  0
	#define StartTempLeaf  0
	#define pro 1
	#define mid 2
	#define aft 3

	// 设计结构体

	/*
		节点设计
			- 基础
				- 数值
				- 左孩子
				- 右孩子
			- 其他
	*/
	
	typedef int ElemType;

	typedef struct BINARY_TREE_NODE
	{
		ElemType data;
		int leftChild;				// 数组中元素节点的下标
		int rightChild;
		int selfInd;
	}BTNode;


	/*
		二叉树：
			- 节点
			- 其他信息
				- 节点总数
				- 深度
				- 叶数
				- 占用空间
	*/

	typedef struct ARRAY_BINARY_TREE
	{
		BTNode* *array;			// 开辟空间，结构体维护此数组
		int total;			// total 总数， 0时刚好是下一个元素插入的位置，也可以作为next insert Index
		int deep;
		int degree;			// 度=2
		int leaf;
		int capacity;		// 二叉树的最大容量(节点个数)， capacity-1 = maxIndex

		 
		BTNode* (*createBTNode)(ElemType data);
		Rstatus (*destroyBTNode)(BTNode* destNode);
		Rstatus (*push)(struct arrBinTree* abtree, ElemType data);
		Rstatus (*printBTree)(struct arrBinTree* abtree, ergodicType code);
		Rstatus (*destroyBinaryTree)(struct arrBinTree* abtree);
		Rstatus (*proPrintBTree)(struct arrBinTree* abtree);

	}arrBinTree;
	
	extern Rstatus binaryTreeInit(arrBinTree* abtree);
	extern void printBTreeInfo(arrBinTree* abtree);



#endif // !__10_BINARY_TREE_REALIZE_H__





