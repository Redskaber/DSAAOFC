#pragma once

#ifndef __03_单向链表的构建_H__
	#define __03_单向链表的构建_H__
	
	typedef int ElemType;
	typedef int Rstatus;
	typedef int NodeCount;

	#define NODE_MARK 0

	typedef struct SINGLE_NODE
	{
		ElemType data;
		struct SingleNode* next;
	}SingleNode, *SNodep;

	typedef struct SINGLE_LINKER
	{
		SNodep headNode;
		SNodep endNode;
		size_t length;
	}SingleLinker;


	extern SingleNode* createNode(ElemType data);
	extern void destroyNode(SingleNode* node);
	extern SingleNode* addNode(SingleLinker* slp, ElemType data);
	extern SingleNode* appendNode(SingleLinker* slp,  ElemType data);
	extern SingleNode* findNode(SingleLinker* slp, ElemType data);
	extern SingleNode* insertNode(SingleLinker* slp, ElemType perdata, ElemType data);
	extern SingleNode* removeNode(SingleLinker* slp, ElemType data);
	extern SingleNode* rfrontNode(SingleLinker* slp);
	extern SingleNode* popNode(SingleLinker* slp);
	extern Rstatus replaceNodeVal(SingleLinker* slp, ElemType Repdata, ElemType data);

	extern void SingleLinkerInit(SingleLinker* slp);
	extern NodeCount SinLinNodePrint(SingleLinker* slp);
	extern void SingleLinkerDestroy(SingleLinker* slp);

	extern SingleNode* _findNode(SingleLinker* slp, SingleNode* findNode);
	extern SingleNode* _findperNode(SingleLinker* slp, SingleNode* findNode);
	extern SingleNode* _addNode(SingleLinker* slp, SingleNode* NewNode);
	extern SingleNode* _appendNode(SingleLinker* slp, SingleNode* NewNode);
	extern SingleNode* _insertNode(SingleLinker* slp, SingleNode* PerNode, SingleNode* NewNode);
	extern SingleNode* _removeNode(SingleLinker* slp, SingleNode* removeNode);
	extern Rstatus _replaceNodeVal(SingleLinker* slp, SingleNode* RepNode, ElemType data);

#endif
