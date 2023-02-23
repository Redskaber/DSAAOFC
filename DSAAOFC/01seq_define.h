#pragma once

#ifndef __SEQ_DEFINE_H__
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>

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

	_status status = {
		.OK = _OK,
		.ISEMRTY = _ISEMRTY,
		.NOTEMRTY = _NOTEMRTY,
		.OVERFLOW = _OVERFLOW,
		.ISDESTROY = _ISDESTROY,
		.INITCOUNTERROR = _INITCOUNTERROR,
		.INDEXOVERFLOW = _INDEXOVERFLOW,
		.INDEXNOTEXIST = _INDEXNOTEXIST,
		.ELEMNOTEXIST = _ELEMNOTEXIST,
		.MALLOCERROR = _MALLOCERROR,

	};

	typedef struct INITCODE 
	{
		int AUTOINITCODE;
		int ARRAYINITCODE;
		int DEFAULTMARK;
	}_initcode;

	_initcode initcode = {
		.AUTOINITCODE = _AUTOINITCODE,
		.ARRAYINITCODE = _ARRAYINITCODE,
		.DEFAULTMARK = _DEFAULTMARK
	};

	typedef struct StaticSQList
	{
		ElemType array[MEMMAX];
		size_t length;
			
	} SSQL;
	
	size_t ArrMemory = MEMMAX * sizeof(ElemType);
	size_t LenMemory = sizeof(size_t);


	/*
		Operation:
			Rstatus SeqListInit(SSQL* Pssl, INITCODE InitCode,...)：初始化操作，选择性auto初始化或者将一个外部的InitArray赋值的前InitCount个给线性表Pssl（顺序表）。返回状态。
			Rstatus SeqListDestroy(SSQL* Pssl)：销毁操作，将顺序表Pssl销毁，释放开辟的空间。返回状态。

			Rstatus SeqListPushBalk(SSQL* Pssl, ElemType Elem)：尾部推入操作，将元素Elem推入顺序表Pssl的尾部。返回状态。
			Rstatus SeqListPushFront(SSQL* Pssl, ElemType Elem)：头部推入操作，将元素Elem推入顺序表Pssl的头部。返回状态。
			Rstatus SeqListInsert(SSQL* Pssl, Index index, ElemType Elem)：插入操作，将元素Elem插入顺序表Pssl的下标(索引)位置index。返回状态。

			Index SeqListIndReplace(SSQL* Pssl, Index index, ElemType NewElem)：修改操作，将顺序表Pssl中的下标index元素替换成Elem。返回index。
			Index SeqListElemReplace(SSQL* Pssl, ElemType OldElem, ElemType NewElem)：修改操作，将顺序表Pssl中的元素OldElem元素替换成NewElem。返回index。
			
			ElemType SeqListPop(SSQL* Pssl, Index index)：弹出操作，将顺序表Pssl中的下标(索引)位置index的值弹出， 返回元素值。
			ElemTypeArray SeqListPopAll(SSQL* Pssl, GETCODE GETRArray)：弹出全部操作，将顺序表Pssl中的所有元素都弹出，GETRArray开启是否需要返回值。返回元素数组。
			Rstatus SeqListRemove(SSQL* Pssl, ElemType Elem)：移除操作，将顺序表Pssl中值为Elem的首个匹配值移除。返回状态。

			Index ElemInSeqList(SSQL* Pssl, ElemType Elem)：元素存在操作，判断元素Elem是否存在Pssl中。返回Index。
			ElemType SeqListGetElem(SSQL* Pssl, Index index)：获取元素操作，获取顺序表Pssl下标为index的元素。返回元素值。
			MemCount SeqListGetLength(SSQL* Pssl)：获取顺序表Pssl的元素个数。返回成员个数。
			Rstatus SeqListIsEmrty(SSQL* Pssl)：判断空表操作，判断顺序表是否是空表。返回状态。
			MemCount SeqListPrint(SSQL* Pssl)：遍历顺序表操作，将顺序表中的元素输出到控制台。返回成员个数。

			集合操作，（多表交集mixed，多表并集union，多表差集diff，多表补集comple）
	*/

	Rstatus SeqListInit(SSQL* Pssl, INITCODE InitCode,...)
	{	
		/*
			user 使用 initArray 数组 初始化 线性表。（O(n)）
			INITCODE InitCode
				- 0 AUTOINITCODE
				- 2 ARRAYINITCODE (initArray， initCount)
		*/
		if (InitCode == initcode.AUTOINITCODE)
		{
			memset(Pssl->array, initcode.DEFAULTMARK, MEMMAX);
			Pssl->length = 0;
			return status.OK;
		}

		ElemTypeArray InitArray;
		size_t InitCount;

		va_list InitArgs;
		va_start(InitArgs, InitCode);
		InitArray = va_arg(InitArgs, ElemTypeArray);
		InitCount = va_arg(InitArgs, size_t);

		if (InitCount > MEMMAX) return status.OVERFLOW;
		Pssl->length = 0;
		for (size_t i = 0; i < InitCount; i++)
		{
			Pssl->array[i] = InitArray[i];
			Pssl->length++;
		}
		if (Pssl->length != InitCount) return status.INITCOUNTERROR;

		va_end(InitArgs);

		return status.OK;
	}

	Rstatus SeqListDestroy(SSQL* Pssl)
	{
		/*
			user 使用 free 函数释放掉SSQL 结构体的空间。
				- malloc
				- calloc
				- realloc
		*/
		free(Pssl);
		Pssl = NULL;
		return status.ISDESTROY;
	}

	Index ElemInSeqList(SSQL* Pssl, ElemType Elem)
	{
		/*
			user 判断元素Elem是否在线性表Pssl中，
				- 不在：-1 (status.INDEXNOTEXIST)
				- 在：index	>=0
		*/
		Index _ind = status.INDEXNOTEXIST;
		for (Index i = 0; i < Pssl->length; i++)
		{
			if (Pssl->array[i] == Elem) {
				_ind = i; break;
			}
		}
		return _ind;
	}

	ElemType SeqListGetElem(SSQL* Pssl, Index index)
	{
		if (index >= 0 && index >= Pssl->length) return status.INDEXOVERFLOW;
		if (index < 0 && -index > Pssl->length) return status.INDEXOVERFLOW;

		ElemType GetElem;
		if (index >= 0) GetElem = Pssl->array[index];
		if (index < 0) GetElem = Pssl->array[Pssl->length + index];

		return GetElem;
	}

	MemCount SeqListGetLength(SSQL* Pssl)
	{
		/*
			user 通过读取 SSQL 中的length属性 get。
		*/
		return Pssl->length;
	}

	Rstatus SeqListIsEmrty(SSQL* Pssl)
	{
		/*
			user 通过判断线性表中的 元素个数是否等于0.
		*/
		if (!Pssl->length) return status.ISEMRTY;
		return status.NOTEMRTY;
	}

	MemCount SeqListPrint(SSQL* Pssl)
	{
		for (size_t i = 0; i < Pssl->length; i++)
		{
			printf("%d ", Pssl->array[i]);
		}
		printf("\n");
		return Pssl->length;
	}

	Rstatus SeqListPushBalk(SSQL* Pssl, ElemType Elem)
	{
		/*
			user 使用 Elem 对线性表进行尾部推入。（O(1)）
		*/
		if (Pssl->length >= MEMMAX) return status.OVERFLOW;
		Pssl->array[Pssl->length] = Elem;
		Pssl->length++;

		return status.OK;
	}

	Rstatus SeqListPushFront(SSQL* Pssl, ElemType Elem)
	{
		/*
			user 使用 Elem 对线性表进行头部推入。（O(n)）
		*/
		if (Pssl->length >= MEMMAX) return status.OVERFLOW;
		for (size_t i = Pssl->length; i > 0; i--)
		{
			Pssl->array[i] = Pssl->array[i-1];
		}
		Pssl->array[0] = Elem;
		Pssl->length++;
		return status.OK;
	}

	Rstatus SeqListInsert(SSQL* Pssl, Index index, ElemType Elem)
	{
		/*
			user 使用 Elem 对线性表 Pssl 的 index 位置进行插入。 （O(1-n)）
		*/
		if (Pssl->length >= MEMMAX) return status.OVERFLOW;
		if (index >= 0 && index > Pssl->length) return status.INDEXOVERFLOW;
		if (index < 0 && -index > Pssl->length) return status.INDEXOVERFLOW;	// Pssl->length + index < 0
		if (SeqListIsEmrty(Pssl) == status.ISEMRTY) SeqListPushBalk(Pssl, Elem);

		for (size_t i = Pssl->length; i > 0; i--)
		{
			if (index >= 0) 
			{
				if (i > index) Pssl->array[i] = Pssl->array[i - 1];
				if (i == index) break;
			}
			else
			{
				size_t _ind = Pssl->length + index;
				if(i > _ind) Pssl->array[i] = Pssl->array[i - 1];
				if (i == _ind) break;
			}
		}
		if (index >= 0) Pssl->array[index] = Elem;
		if (index < 0) Pssl->array[Pssl->length + index] = Elem;
		Pssl->length++;
		return status.OK;
	}

	Index SeqListIndReplace(SSQL* Pssl, Index index, ElemType NewElem)
	{
		/*
			user 通过 传递pssl顺序表中的替换下标位置index，替换成为新的Elem
			return -1 error	(>=0)
		*/
		if (SeqListIsEmrty(Pssl) == status.ISEMRTY) return status.ISEMRTY;
		if ((index >= 0 && index >= Pssl->length)||(index <0 && -index > Pssl->length)) return status.INDEXOVERFLOW;
		if (index >=0) Pssl->array[index] = NewElem;
		if (index < 0) Pssl->array[Pssl->length + index]=NewElem;
		
		return index;
	}

	Index SeqListElemReplace(SSQL* Pssl, ElemType OldElem, ElemType NewElem)
	{
		/*
			user 通过使用Pssl中OldElem，替换成NewElem。 
			return index >=0
		*/
		Index OldIndex = ElemInSeqList(Pssl, OldElem);
		if (OldIndex == status.INDEXNOTEXIST) return status.INDEXNOTEXIST;
		SeqListIndReplace(Pssl, OldIndex, NewElem);
		return OldIndex;
	}

	ElemType SeqListPop(SSQL* Pssl, Index index)
	{
		/*
			user 使用 index 确定弹出元素位置。
		*/
		if (SeqListIsEmrty(Pssl) == status.ISEMRTY) return status.ISEMRTY;
		if (index >= 0 && index >= Pssl->length) return status.INDEXOVERFLOW;
		if (index < 0 && -index > Pssl->length) return status.INDEXOVERFLOW;
		
		ElemType popElem;

		popElem = (index>=0)? (Pssl->array[index]):(Pssl->array[Pssl->length + index]);
		for (size_t i = 1; i < Pssl->length; i++)
		{
			if (index >= 0 && i > index) Pssl->array[i - 1] = Pssl->array[i];
			if(index <0 && i > Pssl->length + index) Pssl->array[i - 1] = Pssl->array[i];
		}
		Pssl->array[Pssl->length - 1] = SEQDEFAULTVAL;
		Pssl->length--;
		return popElem;
	}

	ElemTypeArray SeqListPopAll(SSQL* Pssl, GETCODE GETRArray)
	{
		/*
			user 弹出Pssl 中所有元素 -> 空表
			GETRarray: 
				#define GET 1
				#define NOTGET 0
		*/
		size_t memCount = Pssl->length;
		if (!memCount) return status.ISEMRTY;

		ElemTypeArray TempElemArray = InitTempArray;
		if (GETRArray) 
		{
			size_t memSize = sizeof(Pssl->array[0]);
			TempElemArray = (ElemTypeArray)calloc(memCount, memSize);
		}
		for (size_t i = 0; i < Pssl->length; i++)
		{		
			if (GETRArray) TempElemArray[memCount - (1 + i)] = Pssl->array[memCount - (1 + i)];
			Pssl->array[memCount - (1 + i)] = SEQDEFAULTVAL;
		}
		Pssl->length = 0;
		return TempElemArray;
	}

	Rstatus SeqListRemove(SSQL* Pssl, ElemType Elem)
	{
		/*
			user 移除 Pssl 中的 Elem元素,(默认，从头到尾)。
		*/
		Index _ind = ElemInSeqList(Pssl, Elem);
		if (_ind == -1) return status.ELEMNOTEXIST;

		for (size_t i = _ind; i < Pssl->length; i++)	
		{
			Pssl->array[i] = Pssl->array[i + 1];
		}

		Pssl->array[Pssl->length - 1] = SEQDEFAULTVAL;
		Pssl->length--;

		return status.OK;
	}

#endif
