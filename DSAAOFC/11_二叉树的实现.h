#pragma once

#ifndef __11_二叉树的实现_H__
	#define __11_二叉树的实现_H__
	#include<stdbool.h>
	/*
		通过链表实现二叉树
	*/

	typedef int ElemType;
	typedef int Rstatus;
	#define NotChild -1
	#define NotParent -1
	#define NotBor -1
	#define InitMomery 50

	typedef struct LNODE
	{
		ElemType data;
		struct Lnode* leftChild;
		struct Lnode* rightChild;
		struct Lnode* parent;
		struct Lnode* leftBor;		// 减少工作量（偷懒）
		struct Lnode* rightBor;

	}Lnode;

	typedef struct BINARYTREE
	{
		Lnode* root;
		Lnode* next;
		Lnode* * nodeLis;
		int total;
		int degree;
		int leaf;
		int deep;

		Rstatus (*push)					(struct LBinTree* lbtree, ElemType data);
		bool	(*isEmtryTree)			(struct LBinTree* lbtree);
		Rstatus (*printNodeInfo)		(struct LBinTree* lbtree);
		Rstatus (*printBinTreeInfo)		(struct LBinTree* lbtree);
		Rstatus (*preorderTraversal)	(struct LBinTree* lbtree);
		Rstatus (*midorderTraversal)	(struct LBinTree* lbtree);
		Rstatus (*postorderTraversal)	(struct LBinTree* lbtree);
	}LBinTree;

	extern Rstatus BinTreeInit		(LBinTree* lbtree);
	extern Rstatus BinTreeDestroy	(LBinTree* lbtree);
		
#endif // !__11_二叉树的实现_H__