#pragma once

#ifndef __SEQ_DEFINE_H__
	#define __SEQ_DEFINE_H__

	#define MEMMAX 100
	#define SEQDEFAULTVAL NULL
	#define GET 1
	#define NOTGET 0
	#define InitTempArray {NULL}
	typedef int ElemType;
	typedef int Rstatus;
	typedef int Index;
	typedef int GETCODE;
	typedef int INITCODE;
	typedef int* ElemTypeArray;
	typedef size_t MemCount;

	#define _OK 1	
	#define _SETMARK 0
	#define _ISEMRTY 1
	#define _NOTEMRTY 0
	#define _OVERFLOW -1
	#define _ISDESTROY 1
	#define _INITCOUNTERROR -1
	#define _INDEXOVERFLOW -1
	#define _INDEXNOTEXIST -1
	#define _ELEMNOTEXIST NULL
	#define _MALLOCERROR NULL
	#define _MEMBERS 1
	#define _AUTOINITCODE 0
	#define _ARRAYINITCODE 2
	#define _DEFAULTMARK 0

	typedef struct _STATUS
	{
		int OK;
		int ISEMRTY;
		int NOTEMRTY;
		int OVERFLOW;
		int ISDESTROY;
		int INITCOUNTERROR;
		int INDEXOVERFLOW;
		int INDEXNOTEXIST;
		int ELEMNOTEXIST;
		int MALLOCERROR;
		int AUTOINITCODE;
	} _status;

	typedef struct INITCODE
	{
		int AUTOINITCODE;
		int ARRAYINITCODE;
		int DEFAULTMARK;
	}_initcode;


	typedef struct StaticSQList
	{
		ElemType array[MEMMAX];
		size_t length;

	} SSQL;

	extern _status status;
	extern _initcode initcode;
	extern size_t ArrMemory;
	extern size_t LenMemory;

	extern Rstatus SeqListInit(SSQL* Pssl, INITCODE InitCode, ...);
	extern Rstatus SeqListDestroy(SSQL* Pssl);

	extern Rstatus SeqListPushBalk(SSQL* Pssl, ElemType Elem);
	extern Rstatus SeqListPushFront(SSQL* Pssl, ElemType Elem);
	extern Rstatus SeqListInsert(SSQL* Pssl, Index index, ElemType Elem);

	extern Index SeqListIndReplace(SSQL* Pssl, Index index, ElemType NewElem);
	extern Index SeqListElemReplace(SSQL* Pssl, ElemType OldElem, ElemType NewElem);

	extern ElemType SeqListPop(SSQL* Pssl, Index index);
	extern ElemTypeArray SeqListPopAll(SSQL* Pssl, GETCODE GETRArray);
	extern Rstatus SeqListRemove(SSQL* Pssl, ElemType Elem);

	extern Index ElemInSeqList(SSQL* Pssl, ElemType Elem);
	extern ElemType SeqListGetElem(SSQL* Pssl, Index index);
	extern MemCount SeqListGetLength(SSQL* Pssl);
	extern Rstatus SeqListIsEmrty(SSQL* Pssl);
	extern MemCount SeqListPrint(SSQL* Pssl);

#endif
