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
			Rstatus SeqListInit(SSQL* Pssl, ElemType* InitArray, unsigned int InitCount)����ʼ����������һ���ⲿ��InitArray��ֵ��ǰInitCount�������Ա�Pssl��˳���������״̬��
			Rstatus SeqListDestroy(SSQL* Pssl)�����ٲ�������˳���Pssl���٣��ͷſ��ٵĿռ䡣����״̬��

			Rstatus SeqListPushBalk(SSQL* Pssl, ElemType Elem)��β�������������Ԫ��Elem����˳���Pssl��β��������״̬��
			Rstatus SeqListPushFront(SSQL* Pssl, ElemType Elem)��ͷ�������������Ԫ��Elem����˳���Pssl��ͷ��������״̬��
			Rstatus SeqListInsert(SSQL* Pssl, Index index, ElemType Elem)�������������Ԫ��Elem����˳���Pssl���±�(����)λ��index������״̬��

			Index SeqListIndReplace(SSQL* Pssl, Index index, ElemType NewElem)���޸Ĳ�������˳���Pssl�е��±�indexԪ���滻��Elem������index��
			Index SeqListElemReplace(SSQL* Pssl, ElemType OldElem, ElemType NewElem)���޸Ĳ�������˳���Pssl�е�Ԫ��OldElemԪ���滻��NewElem������index��
			
			ElemType SeqListPop(SSQL* Pssl, Index index)��������������˳���Pssl�е��±�(����)λ��index��ֵ������ ����Ԫ��ֵ��
			ElemTypeArray SeqListPopAll(SSQL* Pssl, GETCODE GETRArray)������ȫ����������˳���Pssl�е�����Ԫ�ض�������GETRArray�����Ƿ���Ҫ����ֵ������Ԫ�����顣
			Rstatus SeqListRemove(SSQL* Pssl, ElemType Elem)���Ƴ���������˳���Pssl��ֵΪElem���׸�ƥ��ֵ�Ƴ�������״̬��

			Index ElemInSeqList(SSQL* Pssl, ElemType Elem)��Ԫ�ش��ڲ������ж�Ԫ��Elem�Ƿ����Pssl�С�����Index��
			ElemType SeqListGetElem(SSQL* Pssl, Index index)����ȡԪ�ز�������ȡ˳���Pssl�±�Ϊindex��Ԫ�ء�����Ԫ��ֵ��
			MemCount SeqListGetLength(SSQL* Pssl)����ȡ˳���Pssl��Ԫ�ظ��������س�Ա������
			Rstatus SeqListIsEmrty(SSQL* Pssl)���жϿձ�������ж�˳����Ƿ��ǿձ�����״̬��
			MemCount SeqListPrint(SSQL* Pssl)������˳����������˳����е�Ԫ�����������̨�����س�Ա������

			���ϲ������������mixed�������union�����diff�������comple��
	*/

	Rstatus SeqListInit(SSQL* Pssl, INITCODE InitCode,...)
	{	
		/*
			user ʹ�� initArray ���� ��ʼ�� ���Ա���O(n)��
			INITCODE InitCode
				- 0 AUTOINITCODE
				- 2 ARRAYINITCODE (initArray�� initCount)
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
			user ʹ�� free �����ͷŵ�SSQL �ṹ��Ŀռ䡣
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
			user �ж�Ԫ��Elem�Ƿ������Ա�Pssl�У�
				- ���ڣ�-1 (status.INDEXNOTEXIST)
				- �ڣ�index	>=0
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
			user ͨ����ȡ SSQL �е�length���� get��
		*/
		return Pssl->length;
	}

	Rstatus SeqListIsEmrty(SSQL* Pssl)
	{
		/*
			user ͨ���ж����Ա��е� Ԫ�ظ����Ƿ����0.
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
			user ʹ�� Elem �����Ա����β�����롣��O(1)��
		*/
		if (Pssl->length >= MEMMAX) return status.OVERFLOW;
		Pssl->array[Pssl->length] = Elem;
		Pssl->length++;

		return status.OK;
	}

	Rstatus SeqListPushFront(SSQL* Pssl, ElemType Elem)
	{
		/*
			user ʹ�� Elem �����Ա����ͷ�����롣��O(n)��
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
			user ʹ�� Elem �����Ա� Pssl �� index λ�ý��в��롣 ��O(1-n)��
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
			user ͨ�� ����pssl˳����е��滻�±�λ��index���滻��Ϊ�µ�Elem
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
			user ͨ��ʹ��Pssl��OldElem���滻��NewElem�� 
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
			user ʹ�� index ȷ������Ԫ��λ�á�
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
			user ����Pssl ������Ԫ�� -> �ձ�
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
			user �Ƴ� Pssl �е� ElemԪ��,(Ĭ�ϣ���ͷ��β)��
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
