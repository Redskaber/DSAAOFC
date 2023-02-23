/*
	逻辑上元素是顺序的

	ADT	线性表（List)

	Data
		线性表的数据对象集合为{a1,a2,..., an}，
		每个元素的类型均为DataType。
		其中，除第一个元素a1外，每一个元素有且只有一个直接前驱元素，
		除了最后一个元素an外，每一个元素有且只有一个直接后继元素。
		数据元素之间的关系是一对一的关系。

	Operation:
		Rstatus SeqListInit(SSQL* Pssl, ElemType* InitArray, unsigned int InitCount)：初始化操作，将一个外部的InitArray赋值的前InitCount个给线性表Pssl（顺序表）。返回状态。
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

	endADT
*/


#include "01seq_define.h"
#include <stdio.h>
#include <stdlib.h>


int start_linear_table()
{
	printf("******************< SeqListInit\t>***************\n");
	size_t initCount1 = 10;
	size_t initCount2 = 10;
	size_t initCount3 = 14;
	int initArray1[] = { 0,1,2,3,4,5,6,7,8,9 };
	int initArray2[] = { 0,1,4,3,4,5,6,7,7,9 };
	int initArray3[] = { 0,1,4,3,4,5,6,7,7,9,10,11,12,13,14,15 };

	SSQL* SL = (SSQL*)malloc(ArrMemory + LenMemory);
	SSQL* SL2 = (SSQL*)malloc(ArrMemory + LenMemory);
	SSQL* SL3 = (SSQL*)malloc(ArrMemory + LenMemory);
	SSQL* SL4 = (SSQL*)malloc(ArrMemory + LenMemory);
	Rstatus initCode1 = SeqListInit(SL, initcode.ARRAYINITCODE, initArray1, initCount1);
	Rstatus initCode2 = SeqListInit(SL2, 2,initArray2, initCount2);
	Rstatus initCode3 = SeqListInit(SL3, _ARRAYINITCODE,initArray3, initCount3);
	Rstatus initCode4 = SeqListInit(SL4, initcode.AUTOINITCODE);

	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);

	printf("******************< SeqListPushBalk\t>***************\n");
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);
	if (initCode1 == status.OK) SeqListPushBalk(SL, 10);
	if (initCode2 == status.OK) SeqListPushBalk(SL2, 10);
	if (initCode3 == status.OK) SeqListPushBalk(SL3, 10);
	if (initCode4 == status.OK) SeqListPushBalk(SL4, 10);
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);

	printf("******************< SeqListPushFront\t>***************\n");
	SeqListPushFront(SL, -1);
	SeqListPushFront(SL2, -1);
	SeqListPushFront(SL3, -1);
	SeqListPushFront(SL4, -1);
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);

	printf("******************< SeqListInsert\t>***************\n");
	ElemType InsertElem = 5;
	Index ind = 5, Nind = -1, Overind = -14;
	SeqListInsert(SL, ind, InsertElem);		SeqListPrint(SL);
	SeqListInsert(SL, Nind, InsertElem);	SeqListPrint(SL);
	SeqListInsert(SL, Overind, InsertElem);	SeqListPrint(SL);
	printf("\n");
	SeqListInsert(SL, ind, InsertElem);		SeqListPrint(SL2);
	SeqListInsert(SL, Nind, InsertElem);	SeqListPrint(SL2);
	SeqListInsert(SL, Overind, InsertElem);	SeqListPrint(SL2);
	printf("\n");
	SeqListInsert(SL, ind, InsertElem);		SeqListPrint(SL3);
	SeqListInsert(SL, Nind, InsertElem);	SeqListPrint(SL3);
	SeqListInsert(SL, Overind, InsertElem);	SeqListPrint(SL3);
	printf("\n");
	SeqListInsert(SL, ind, InsertElem);		SeqListPrint(SL4);
	SeqListInsert(SL, Nind, InsertElem);	SeqListPrint(SL4);
	SeqListInsert(SL, Overind, InsertElem);	SeqListPrint(SL4);
	printf("\n");

	printf("******************< SeqListIndReplace\t>***************\n");
	ElemType NewElem = 30;
	Index Rind = 3;
	Index RsInd1 = SeqListIndReplace(SL, Rind, NewElem);
	Index RsInd2 = SeqListIndReplace(SL2, Rind, NewElem);
	Index RsInd3 = SeqListIndReplace(SL3, Rind, NewElem);
	Index RsInd4 = SeqListIndReplace(SL4, Rind, NewElem);
	if (RsInd1 == status.INDEXNOTEXIST) printf("index1:%d\n is not exist", Rind);
	if (RsInd2 == status.INDEXNOTEXIST) printf("index2:%d\n is not exist", Rind);
	if (RsInd3 == status.INDEXNOTEXIST) printf("index3:%d\n is not exist", Rind);
	if (RsInd4 == status.INDEXNOTEXIST) printf("index4:%d\n is not exist", Rind);
	SeqListPrint(SL);

	printf("******************< SeqListElemReplace\t>***************\n");
	ElemType OldElem = 9;
	NewElem = 90;
	RsInd1 = SeqListElemReplace(SL, OldElem, NewElem);
	RsInd2 = SeqListElemReplace(SL2, OldElem, NewElem);
	RsInd3 = SeqListElemReplace(SL3, OldElem, NewElem);
	RsInd4 = SeqListElemReplace(SL4, OldElem, NewElem);
	if (RsInd1 == status.INDEXNOTEXIST) printf("OldElem1:%d\n is not exist", OldElem);
	if (RsInd2 == status.INDEXNOTEXIST) printf("OldElem2:%d\n is not exist", OldElem);
	if (RsInd3 == status.INDEXNOTEXIST) printf("OldElem3:%d\n is not exist", OldElem);
	if (RsInd4 == status.INDEXNOTEXIST) printf("OldElem4:%d\n is not exist", OldElem);
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);

	printf("******************< SeqListPop\t>***************\n");
	Index indp = 5;
	Index Nindp = -5;

	ElemType Rp11 = SeqListPop(SL, indp);
	ElemType Rp12 = SeqListPop(SL2, indp);
	ElemType Rp13 = SeqListPop(SL3, indp);
	ElemType Rp14 = SeqListPop(SL4, indp);
	printf("RP11:%d\n", Rp11); SeqListPrint(SL);
	printf("RP12:%d\n", Rp12); SeqListPrint(SL2);
	printf("RP13:%d\n", Rp13); SeqListPrint(SL3);
	printf("RP14:%d\n", Rp14); SeqListPrint(SL4);
	ElemType Rp21 = SeqListPop(SL, Nindp);
	ElemType Rp22 = SeqListPop(SL2, Nindp);
	ElemType Rp23 = SeqListPop(SL3, Nindp);
	ElemType Rp24 = SeqListPop(SL4, Nindp);
	printf("RP21:%d\n", Rp21); SeqListPrint(SL);
	printf("RP22:%d\n", Rp22); SeqListPrint(SL2);
	printf("RP23:%d\n", Rp23); SeqListPrint(SL3);
	printf("RP24:%d\n", Rp24); SeqListPrint(SL4);

	printf("******************< SeqListRemove\t>***************\n");
	ElemType RElem = 4;

	Rstatus removeCode1 = SeqListRemove(SL, RElem);
	Rstatus removeCode2 = SeqListRemove(SL2, RElem);
	Rstatus removeCode3 = SeqListRemove(SL3, RElem);
	Rstatus removeCode4 = SeqListRemove(SL4, RElem);
	printf("removeCode1:%d\n", removeCode1); SeqListPrint(SL);
	printf("removeCode2:%d\n", removeCode2); SeqListPrint(SL2);
	printf("removeCode3:%d\n", removeCode3); SeqListPrint(SL3);
	printf("removeCode4:%d\n", removeCode4); SeqListPrint(SL4);

	printf("******************< SeqListGetElem\t>***************\n");
	ElemType Elem;
	Elem = SeqListGetElem(SL, 2);
	if (Elem != status.INDEXNOTEXIST) printf("getelem1:%d\n", Elem);
	Elem = SeqListGetElem(SL2, 2);
	if (Elem != status.INDEXNOTEXIST) printf("getelem2:%d\n", Elem);
	Elem = SeqListGetElem(SL3, 2);
	if (Elem != status.INDEXNOTEXIST) printf("getelem3:%d\n", Elem);
	Elem = SeqListGetElem(SL4, 2);
	if (Elem != status.INDEXNOTEXIST) printf("getelem4:%d\n", Elem);

	printf("******************< SeqListGetLength\t>***************\n");
	printf("MemCount1:%zd\n", SeqListGetLength(SL));
	printf("MemCount2:%zd\n", SeqListGetLength(SL2));
	printf("MemCount3:%zd\n", SeqListGetLength(SL3));
	printf("MemCount4:%zd\n", SeqListGetLength(SL4));

	printf("******************< SeqListIsEmrty\t>***************\n");
	Rstatus IsEmrty1;
	Rstatus IsEmrty2;
	Rstatus IsEmrty3;
	Rstatus IsEmrty4;

	printf("isEmrty1:%d\n", IsEmrty1 = SeqListIsEmrty(SL));
	if (IsEmrty1 != status.ISEMRTY) SeqListPrint(SL);
	printf("isEmrty2:%d\n", IsEmrty2 = SeqListIsEmrty(SL2));
	if (IsEmrty2 != status.ISEMRTY) SeqListPrint(SL2);
	printf("isEmrty3:%d\n", IsEmrty3 = SeqListIsEmrty(SL3));
	if (IsEmrty3 != status.ISEMRTY) SeqListPrint(SL3);
	printf("isEmrty4:%d\n", IsEmrty4 = SeqListIsEmrty(SL4));
	if (IsEmrty4 != status.ISEMRTY) SeqListPrint(SL4);

	printf("******************< SeqListPopAll\t>***************\n");
	// ElemTypeArray RArray =  SeqListPopAll(SL,GET);
	printf("before;\n");
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);
	SeqListPopAll(SL, NOTGET);
	SeqListPopAll(SL2, NOTGET);
	SeqListPopAll(SL3, NOTGET);
	SeqListPopAll(SL4, NOTGET);
	printf("after;\n");
	SeqListPrint(SL);
	SeqListPrint(SL2);
	SeqListPrint(SL3);
	SeqListPrint(SL4);

	printf("******************< SeqListIsEmrty\t>***************\n");
	printf("isEmrty1:%d\n", IsEmrty1 = SeqListIsEmrty(SL));
	if (IsEmrty1 != status.ISEMRTY) SeqListPrint(SL);
	printf("isEmrty2:%d\n", IsEmrty2 = SeqListIsEmrty(SL2));
	if (IsEmrty2 != status.ISEMRTY) SeqListPrint(SL2);
	printf("isEmrty3:%d\n", IsEmrty3 = SeqListIsEmrty(SL3));
	if (IsEmrty3 != status.ISEMRTY) SeqListPrint(SL3);
	printf("isEmrty4:%d\n", IsEmrty4 = SeqListIsEmrty(SL4));
	if (IsEmrty4 != status.ISEMRTY) SeqListPrint(SL4);

	printf("******************< SeqListDestroy\t>***************\n");
	Rstatus destroy1;
	Rstatus destroy2;
	Rstatus destroy3;
	Rstatus destroy4;

	printf("isDestroy:%d\n", destroy1 = SeqListDestroy(SL));
	if (destroy1 != status.ISDESTROY)  SeqListPrint(SL);
	printf("isDestroy:%d\n", destroy2 = SeqListDestroy(SL2));
	if (destroy2 != status.ISDESTROY)  SeqListPrint(SL2);
	printf("isDestroy:%d\n", destroy3 = SeqListDestroy(SL3));
	if (destroy3 != status.ISDESTROY)  SeqListPrint(SL3);
	printf("isDestroy:%d\n", destroy4 = SeqListDestroy(SL4));
	if (destroy4 != status.ISDESTROY)  SeqListPrint(SL4);

	return 0;
}