#pragma once

#ifndef __04_双向链表的构建_H__
	#define __04_双向链表的构建_H__

	typedef int ElemType;
	typedef int Rstatus;

	typedef struct BIDLNODE
	{
		ElemType data;
		struct BNode* perNode;
		struct BNode* afterNode;

	}BNode;

	typedef struct BIDIRECTIONAL_LINKER
	{
		BNode* headNode;
		BNode* endNode;
		size_t length;

	}BiDLinker;


	extern Rstatus BidLinkerInit(BiDLinker* bdlp);
	extern Rstatus BidLinkPrint(BiDLinker* bdlp);


	extern BNode* createBNode(ElemType data);
	extern Rstatus destroyBNode(BNode* node);


	extern BNode* addBNode(BiDLinker* bdlp, ElemType data);
	extern BNode* appendBNode(BiDLinker* bdlp, ElemType data);
	extern BNode* insertBNode(BiDLinker* bdlp, ElemType afterData, ElemType data);
	extern BNode* removeBNode(BiDLinker* bdlp, ElemType data);
	extern BNode* frontRemoveBNode(BiDLinker* bdlp);
	extern BNode* popBNode(BiDLinker* bdlp);
	extern BNode* replaceBNode(BiDLinker* bdlp, ElemType reData, ElemType data);
	extern BNode* findBNode(BiDLinker* bdlp, ElemType data);


	extern BNode* _addBNode(BiDLinker* bdlp, BNode* node);
	extern BNode* _appendBNode(BiDLinker* bdlp, BNode* node);
	extern BNode* _insertBNode(BiDLinker* bdlp, BNode* afterNode, BNode* node);
	extern BNode* _removeBNode(BiDLinker* bdlp, BNode* reNode);
	extern BNode* _frontRemoveBNode(BiDLinker* bdlp);
	extern BNode* _popBNode(BiDLinker* bdlp);
	extern BNode* _replaceBNode(BiDLinker* bdlp, BNode* reNode, BNode* node);
	extern BNode* _findBNode(BiDLinker* bdlp, BNode* node);

#endif
