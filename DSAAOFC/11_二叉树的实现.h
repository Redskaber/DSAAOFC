#pragma once

#ifndef __11_��������ʵ��_H__
	#define __11_��������ʵ��_H__
	#include<stdbool.h>
	/*
		ͨ������ʵ�ֶ�����
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
		struct Lnode* leftBor;		// ���ٹ�������͵����
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
		
#endif // !__11_��������ʵ��_H__