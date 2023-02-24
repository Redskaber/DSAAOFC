#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include "02_动态顺序表的构建.h"

/*
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
*/

_InitCode _initcode = {
	.AUTO = _AUTO,
	.USE_ARRAY = _USE_ARRAY,
	.DEFAULT_LENGTH = _DEFAULT_LENGTH,
	.DEFAULT_MAXSIZE = _DEFAULT_MAXSIZE,
	.INIT_UP_MULTIPLE = _INIT_UP_MULTIPLE,
	.UP_CAPACITY_MULTIPLE = _UP_CAPACITY_MULTIPLE
};

_Rstatus status = {
	.OK = _OK
};

_Error error = {
	.INDEX_OVERFLOW = _INDEX_OVERFLOW,
	.INIT_COUNT_ERROR = _INIT_COUNT_ERROR,
	.INITCODE_ERROR = _INITCODE_ERROR,
	.INIT_MALLOC_ERROR = _INIT_MALLOC_ERROR,
	.INIT_CAPACITY_ERROR = _INIT_CAPACITY_ERROR,
	.REALLOC_UPCAPACITY_ERROR = _REALLOC_UPCAPACITY_ERROR,
	.ELEM_NOT_EXIST = _ELEM_NOT_EXIST
};

_ModeHandle ModeHandle = {
	.Pop = _POPMODE,
	.Remove = _REMOVEMODE
};


Index ElemInDSeqList(DSEQL* Dslp, ElemType Elem);
Index _DSeqListIndexHandle(DSEQL* Dslp, Index index);
ElemType _DSeqListRemoveHandle(DSEQL* Dslp, Index index, HandleMode getmode);


Rstatus DSeqListInit(DSEQL* Dslp, InitCode initcode,...)
{
	/*
		1.auto -> 
		2.input	-> (ElemType*)array + (int)count

		auto:
			- darray -> 开辟一块默认大小的空间。
			- length -> 默认创建时元素个数 0
			- capacity -> 开辟空间容纳的元素最大数, 默认2倍增量，初始值为50。
	*/
	if (initcode == _initcode.AUTO)
	{
		Dslp->darray = (ElemType *)malloc(_initcode.DEFAULT_MAXSIZE * sizeof(ElemType));
		Dslp->length = _initcode.DEFAULT_LENGTH;
		Dslp->capacity = _initcode.DEFAULT_MAXSIZE;
		
		return status.OK;
	}

	if (initcode == _initcode.USE_ARRAY)
	{
		Dslp->darray = NULL;
		Dslp->length = 0;
		Dslp->capacity = 0;

		va_list InitArgs;
		va_start(InitArgs, initcode);

		ElemType* InitArray = va_arg(InitArgs, ElemType*);
		int InitCount = va_arg(InitArgs, int);

		if (InitCount <= 0) return error.INIT_COUNT_ERROR;
		if (InitCount < (_initcode.DEFAULT_MAXSIZE / 2)) Dslp->capacity = _initcode.DEFAULT_MAXSIZE;
		if (InitCount >= (_initcode.DEFAULT_MAXSIZE / 2))
		{
			size_t Multiple = InitCount / _initcode.DEFAULT_MAXSIZE;
			Dslp->capacity = (Multiple + _initcode.INIT_UP_MULTIPLE) * _initcode.DEFAULT_MAXSIZE;		// 100(0-50), 150(51-100), 200(101-150),...

		}
		if (Dslp->capacity <= InitCount) return error.INIT_CAPACITY_ERROR;

		Dslp->darray = (ElemType*)malloc(Dslp->capacity * sizeof(ElemType));
		if (Dslp->darray == NULL) return error.INIT_MALLOC_ERROR;

		for (int eind = 0; eind < InitCount; eind++)
		{
			Dslp->darray[eind] = InitArray[eind];
			Dslp->length++;
		}
		if (Dslp->length != InitCount) return error.INIT_COUNT_ERROR;

		va_end(InitArgs);
		return status.OK;
	}
	return error.INITCODE_ERROR;
}

Rstatus DSeqListDestroy(DSEQL* Dslp)
{
	/*
		Dslp->
			darray		释放 + NULL
			length		0
			capacity	0
	*/
	free(Dslp->darray);
	Dslp->darray = NULL;
	Dslp->length = 0;
	Dslp->capacity = 0;
	return status.OK;
}

Rstatus DSeqListUpCapacity(DSEQL* Dslp)
{
	/*
		扩容（默认,以原来容量的2倍扩容，可以选择手动扩容） 检测并扩容
			- 修改 status.UP_CAPACITY_MULTIPLE || _UP_CAPACITY_MULTIPLE
	*/
	if (Dslp->capacity == Dslp->length)
	{	
		int ElemSize = sizeof(ElemType);
		size_t NewCapacity = (Dslp->length == 0) ? (ElemSize) : (_initcode.UP_CAPACITY_MULTIPLE * Dslp->capacity);
		ElemType* NewDArr = realloc(Dslp->darray, NewCapacity * ElemSize);
		if (NewDArr == NULL) return error.REALLOC_UPCAPACITY_ERROR;
		Dslp->darray = NewDArr;
		Dslp->capacity = NewCapacity;
	}
	return status.OK;
}

Rstatus DSeqListPushBalk(DSEQL* Dslp, ElemType Elem)
{
	/*
		[0,1,2,3,4,5,6]	<- 7
		index  = length
	*/
	DSeqListUpCapacity(Dslp);	

	Dslp->darray[Dslp->length] = Elem;
	Dslp->length++;
	return status.OK;
}

Rstatus DSeqListPushFront(DSEQL* Dslp, ElemType Elem) 
{
	/*
		7 -> [0,1,2,3,4,5,6]
		index = 0;
		->	index = idnex+1
	*/
	DSeqListUpCapacity(Dslp);

	for (size_t afterInd = Dslp->length; afterInd > 0; afterInd--)
	{
		size_t beforeInd = afterInd - 1;
		Dslp->darray[afterInd] = Dslp->darray[beforeInd];
	}
	Dslp->darray[0] = Elem;
	Dslp->length++;
	return status.OK;
}

Rstatus DSeqListInsert(DSEQL* Dslp, Index index, ElemType ELem)
{
	/*
		[0,1,2,3,4,5,6] 
		7 -> index
			index(>=) 0
				- before x
				- after index = index -1;
	*/
	DSeqListUpCapacity(Dslp);
	index = _DSeqListIndexHandle(Dslp, index);
	if (index < 0) return error.INDEX_OVERFLOW;

	for (int afterInd = Dslp->length; afterInd > index; afterInd--)		// size_t unsigned  && -- -> warning
	{
		int beforeInd = afterInd - 1;
		Dslp->darray[afterInd] = Dslp->darray[beforeInd];
	}
	Dslp->darray[index] = ELem;
	Dslp->length++;

	return status.OK;
}

Rstatus DSeqListToIndRemove(DSEQL* Dslp, Index index)
{
	/*
		[0,1,2,3,4,5,6]
		 if index in []
		 ind = ind+1
		 len-1 > MARK
		 len--
	*/
	return _DSeqListRemoveHandle(Dslp, index, ModeHandle.Remove);
}

Rstatus DSeqListToElemRemove(DSEQL* Dslp, ElemType Elem)
{
	/*
		[0,1,2,3,4,5,6] 
		if 3 in [];
			- in	 get index	-> indRemove
			- n'in	 error
	*/
	Index Rindex = ElemInDSeqList(Dslp, Elem);
	if (Rindex < 0) return error.ELEM_NOT_EXIST;
	return DSeqListToIndRemove(Dslp, Rindex);
}

ElemType DSeqListIndPop(DSEQL* Dslp, Index index)
{
	/*
		[0,1,2,3,4,5,6]
		-> ? index
		-> get elem
		return elem
	*/
	return _DSeqListRemoveHandle(Dslp, index, ModeHandle.Pop);
}

ElemType* DSeqListIndPopAll(DSEQL* Dslp)
{
	/*
		[0,1,2,3,4,5,6]
		-> []
	*/
	ElemType* TempArr = Dslp->darray;
	memset(Dslp->darray, MARK, Dslp->length);
	Dslp->length = 0;

	return TempArr;
}

Rstatus DSeqListToElemReplace(DSEQL* Dslp, ElemType OldElem, ElemType NewElem)
{
	/*
		[0,1,2,3,4,5,6]
		if OldElem in []
		-> Oldind
		[][Oldind] = NewElem
	*/

	Index OldIndex = ElemInDSeqList(Dslp, OldElem);
	if (OldIndex < 0) return error.ELEM_NOT_EXIST;

	Dslp->darray[OldIndex] = NewElem;
	return status.OK;
}

Rstatus DSeqListToIndReplace(DSEQL* Dslp, Index index, ElemType NewElem)
{
	/*
		[0,1,2,3,4,5,6]
		if index in []
		[][index] = NewElem
	*/
	index = _DSeqListIndexHandle(Dslp, index);
	if (index < 0) return error.INDEX_OVERFLOW;

	Dslp->darray[index] = NewElem;
	return status.OK;
}

ElemType _DSeqListRemoveHandle(DSEQL* Dslp, Index index, HandleMode getmode)
{
	/*
		getmode: 
			-ModeHandle.pop		1
			-ModeHandle.remove	0
	*/
	index = _DSeqListIndexHandle(Dslp, index);
	if (index < 0) return error.INDEX_OVERFLOW;

	ElemType popElem;
	if (getmode == ModeHandle.Pop)popElem = Dslp->darray[index];

	Index UpInd = Dslp->length - 1;
	for (int ind = index; ind < UpInd; ind++)
	{
		Dslp->darray[ind] = Dslp->darray[ind + 1];
	}
	Dslp->darray[UpInd] = MARK;
	Dslp->length--;

	if (getmode == ModeHandle.Pop) return popElem;
	
	return (void*)status.OK;
}

Index _DSeqListIndexHandle(DSEQL* Dslp, Index index)
{
	// error -1, index >= 0
	Index lowInd = 0;
	Index UpInd = (Index)Dslp->length - 1;
	if (index >= lowInd) 
	{
		if (index > UpInd) return error.INDEX_OVERFLOW;
		return index;
	}
	if (index < lowInd)
	{ 
		if (-index > UpInd + 1) return error.INDEX_OVERFLOW;
		return UpInd + 1 + index;
	}
	return error.INDEX_OVERFLOW;
}

Index ElemInDSeqList(DSEQL* Dslp, ElemType Elem)
{
	/*
		[0,1,2,3,4,5,6]
		
		3  ? in []
		7  ? in []
		-> for
		index >=0 v
		index < 0 x
	*/
	Index TempIndex = -1;
	for (int ind = 0; ind < Dslp->length; ind++)
	{
		if (Dslp->darray[ind] == Elem) { TempIndex = ind; break; }
	}
	return TempIndex;
}

ElemType DSeqListGetElem(DSEQL* Dslp, Index index)
{
	/*
		[0,1,2,3,4,5,6]
		index in range
		get index -> elem
	*/
	index = _DSeqListIndexHandle(Dslp, index);
	if (index < 0) return error.INDEX_OVERFLOW;

	return Dslp->darray[index];

}

Length DSeqListGetLength(DSEQL* Dslp)
{
	return (Length)Dslp->length;
}

Rstatus DSeqListPrint(DSEQL* Dslp)
{
	for (size_t eind = 0; eind < Dslp->length; eind++)
	{
		printf("%d ",Dslp->darray[eind]);
	}
	printf("\n");
	return (int)Dslp->length;
}
