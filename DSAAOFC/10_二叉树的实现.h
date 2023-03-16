#pragma once

#ifndef __10_BINARY_TREE_REALIZE_H__
	#define __10_BINARY_TREE_REALIZE_H__
	
	/*
		ʹ��˳���Ϊ��׼�Ķ����� *
		ʹ������Ϊ��׼�Ķ�����
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

	// ��ƽṹ��

	/*
		�ڵ����
			- ����
				- ��ֵ
				- ����
				- �Һ���
			- ����
	*/
	
	typedef int ElemType;

	typedef struct BINARY_TREE_NODE
	{
		ElemType data;
		int leftChild;				// ������Ԫ�ؽڵ���±�
		int rightChild;
		int selfInd;
	}BTNode;


	/*
		��������
			- �ڵ�
			- ������Ϣ
				- �ڵ�����
				- ���
				- Ҷ��
				- ռ�ÿռ�
	*/

	typedef struct ARRAY_BINARY_TREE
	{
		BTNode* *array;			// ���ٿռ䣬�ṹ��ά��������
		int total;			// total ������ 0ʱ�պ�����һ��Ԫ�ز����λ�ã�Ҳ������Ϊnext insert Index
		int deep;
		int degree;			// ��=2
		int leaf;
		int capacity;		// ���������������(�ڵ����)�� capacity-1 = maxIndex

		 
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





