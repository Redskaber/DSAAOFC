#pragma once


#ifndef __02_动态顺序表的构建_H__
	#define __02_动态顺序表的构建_H__
	
	typedef int ElemType;
	typedef int InitCode;
	typedef int Rstatus;
	typedef int Index;
	typedef int HandleMode;
	typedef int Length;
	#define _AUTO 0
	#define _USE_ARRAY 2
	#define _DEFAULT_LENGTH 0
	#define _DEFAULT_MAXSIZE 50
	#define _INIT_UP_MULTIPLE 2
	#define _UP_CAPACITY_MULTIPLE 2

	#define _OK 1

	#define _INIT_COUNT_ERROR -1
	#define _INDEX_OVERFLOW -1
	#define _INITCODE_ERROR -1
	#define _INIT_MALLOC_ERROR -1
	#define _INIT_CAPACITY_ERROR -1
	#define _REALLOC_UPCAPACITY_ERROR -1
	#define _ELEM_NOT_EXIST -1

	#define MARK NULL
	#define _POPMODE 1
	#define _REMOVEMODE 0

	typedef struct DynamicSEQL
	{
		ElemType* darray;
		size_t length;
		size_t capacity;
	}DSEQL;

	typedef struct INITCODE
	{
		int AUTO;
		int USE_ARRAY;
		int DEFAULT_LENGTH;
		int DEFAULT_MAXSIZE;
		int INIT_UP_MULTIPLE;
		int UP_CAPACITY_MULTIPLE;
	}_InitCode;

	typedef struct ERROR
	{
		int INIT_COUNT_ERROR;
		int INDEX_OVERFLOW;
		int INITCODE_ERROR;
		int INIT_MALLOC_ERROR;
		int INIT_CAPACITY_ERROR;
		int REALLOC_UPCAPACITY_ERROR;
		int ELEM_NOT_EXIST;
	}_Error;

	typedef struct RSTATUS
	{
		int OK;
	}_Rstatus;

	typedef struct MODEHANDLE
	{
		int Remove;
		int Pop;
	}_ModeHandle;

	extern _InitCode _initcode;
	extern _Rstatus status;
	extern _Error error;

	extern Rstatus DSeqListInit(DSEQL* Dslp, InitCode initcode, ...);
	extern Rstatus DSeqListDestroy(DSEQL* Dslp);
	extern Rstatus DSeqListPushBalk(DSEQL* Dslp, ElemType Elem);
	extern Rstatus DSeqListPushFront(DSEQL* Dslp, ElemType Elem);
	extern Rstatus DSeqListInsert(DSEQL* Dslp, Index index, ElemType ELem);
	extern Rstatus DSeqListToIndRemove(DSEQL* Dslp, Index index);
	extern Rstatus DSeqListToElemRemove(DSEQL* Dslp, ElemType Elem);
	extern ElemType DSeqListIndPop(DSEQL* Dslp, Index index);
	extern ElemType* DSeqListIndPopAll(DSEQL* Dslp);
	extern Rstatus DSeqListToIndReplace(DSEQL* Dslp, Index index, ElemType NewElem);
	extern Rstatus DSeqListToElemReplace(DSEQL* Dslp, ElemType OldElem, ElemType NewElem);
	extern Index ElemInDSeqList(DSEQL* Dslp, ElemType Elem);
	extern ElemType DSeqListGetElem(DSEQL* Dslp, Index index);
	extern Length DSeqListGetLength(DSEQL* Dslp);
	extern Rstatus DSeqListPrint(DSEQL* Dslp);
	extern Rstatus DSeqListUpCapacity(DSEQL* Dslp);
	 
#endif
