/*
	逻辑上元素是顺序的

	ADT	线性表（List)

	Data
		线性表的数据对象集合为{a1,a2,..., an}，
		每个元素的类型均为DataType。
		其中，除第一个元素a1外，每一个元素有且只有一个直接前驱元素，
		除了最后一个元素an外，每一个元素有且只有一个直接后继元素。
		数据元素之间的关系是一对一的关系。

	Operation
		InitList(&L)：初始化表。构造一个空的线性表L,分配内存空间。
		DestroyList(&L)：销毁操作。销毁线性表，并释放线性表L所占用的内存空间。

		ListInsert(&L,i,e)：插入操作。在表L中的第i个位置上插入指定元素e。
		ListDelete(&l,i,&e)：删除操作。删除表L中第i个位置的元素，并用e返回删除元素的值。

		LocateElem(L,e)：按值查找操作。在表L中查找具有给定关键字值的元素。
		GetElem(L,i)：按位查找操作。获取表L中第i个位置的元素的值。
		其他常用操作：
		Length(L):求表长。返回线性表L的长度，即L中数据元素的个数。
		PrintList(L):输出操作。按前后顺序输出线性表L的所有值。
		Emrty(L):判空操作。若L为空表，则返回true,否则返回false。

	endADT
*/


#include "01seq_define.h"
#include <stdio.h>
#include <stdlib.h>


int start_linear_table()
{
	printf("******************< SeqListInit\t>***************\n");
	size_t initCount = 10;
	int initArray1[] = { 0,1,2,3,4,5,6,7,8,9 };
	int initArray2[] = { 0,1,4,3,4,5,6,7,7,9 };

	SSQL* SL = (SSQL*)malloc(ArrMemory + LenMemory);
	SSQL* SL2 = (SSQL*)malloc(ArrMemory + LenMemory);
	Rstatus initCode1 = SeqListInit(SL, initArray1, initCount);
	Rstatus initCode2 = SeqListInit(SL2, initArray2, initCount);

	SeqListPrint(SL);
	printf("******************< SeqListMixedSet\t>***************\n");
	ElemTypeArray Rmixed = SeqListMixedSet(2, SL, SL2);
	SeqListPrint(SL);
	SeqListPrint(SL2);
	for (size_t i = 0; i < SeqListGetLength(SL); i++)
	{
		printf("%d ", Rmixed[i]);
	}
	printf("\n");

	free(Rmixed);
	Rmixed = NULL;

	printf("******************< SeqListPushBalk\t>***************\n");
	if (initCode1 == status.OK) SeqListPushBalk(SL, 10);	
	SeqListPrint(SL);

	printf("******************< SeqListPushFront\t>***************\n");
	SeqListPushFront(SL, -1);	
	SeqListPrint(SL);

	printf("******************< SeqListInsert\t>***************\n");
	ElemType InsertElem = 5;
	Index ind = 5, Nind = -1, Overind = -14;
	SeqListInsert(SL, ind, InsertElem);		SeqListPrint(SL);
	SeqListInsert(SL, Nind, InsertElem);	SeqListPrint(SL);
	SeqListInsert(SL, Overind, InsertElem);	SeqListPrint(SL);

	printf("******************< SeqListIndReplace\t>***************\n");
	ElemType NewElem = 30;
	Index Rind = 3;
	Index RsInd = SeqListIndReplace(SL, Rind, NewElem);
	if (RsInd == status.INDEXNOTEXIST) printf("index:%d\n is not exist",Rind);
	SeqListPrint(SL);

	printf("******************< SeqListElemReplace\t>***************\n");
	ElemType OldElem = 9;
	NewElem = 90;
	RsInd = SeqListElemReplace(SL, OldElem, NewElem);
	if (RsInd == status.INDEXNOTEXIST) printf("OldElem:%d\n is not exist", OldElem);
	SeqListPrint(SL);

	printf("******************< SeqListPop\t>***************\n");
	Index indp = 5;
	Index Nindp = -5;

	ElemType Rp1 = SeqListPop(SL, indp);
	printf("RP1:%d\n", Rp1); SeqListPrint(SL);
	ElemType Rp2 = SeqListPop(SL, Nindp);
	printf("RP2:%d\n", Rp2); SeqListPrint(SL);
	
	printf("******************< SeqListRemove\t>***************\n");
	ElemType RElem = 4;

	Rstatus removeCode =  SeqListRemove(SL, RElem);
	printf("removeCode:%d\n",removeCode); SeqListPrint(SL);
	
	printf("******************< SeqListGetElem\t>***************\n");
	printf("getelem:%d\n", SeqListGetElem(SL, 2));

	printf("******************< SeqListGetLength\t>***************\n");
	printf("MemCount:%zd\n",SeqListGetLength(SL));

	printf("******************< SeqListMixedSet\t>***************\n");
	set.SETMARK = -1;
	Rmixed =  SeqListMixedSet(2,SL,SL2);
	SeqListPrint(SL);
	SeqListPrint(SL2);
	for (size_t i = 0; i < SeqListGetLength(SL); i++)
	{
		printf("%d ", Rmixed[i]);
	}
	printf("\n");

	free(Rmixed);
	Rmixed = NULL;

	printf("******************< SeqListIsEmrty\t>***************\n");
	Rstatus IsEmrty;

	printf("isEmrty:%d\n", IsEmrty = SeqListIsEmrty(SL)); 
	if (IsEmrty != status.ISEMRTY) SeqListPrint(SL);
	
	printf("******************< SeqListPopAll\t>***************\n");
	// ElemTypeArray RArray =  SeqListPopAll(SL,GET);
	SeqListPopAll(SL,NOTGET);
	SeqListPrint(SL);

	printf("******************< SeqListIsEmrty\t>***************\n");
	printf("isEmrty:%d\n", IsEmrty = SeqListIsEmrty(SL));
	if (IsEmrty != status.ISEMRTY) SeqListPrint(SL);

	printf("******************< SeqListDestroy\t>***************\n");
	Rstatus destroy;

	printf("isDestroy:%d\n", destroy = SeqListDestroy(SL));
	if(destroy != status.ISDESTROY)  SeqListPrint(SL);

	return 0;
}