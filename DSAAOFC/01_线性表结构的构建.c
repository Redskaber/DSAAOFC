/*
	�߼���Ԫ����˳���

	ADT	���Ա�List)

	Data
		���Ա�����ݶ��󼯺�Ϊ{a1,a2,..., an}��
		ÿ��Ԫ�ص����;�ΪDataType��
		���У�����һ��Ԫ��a1�⣬ÿһ��Ԫ������ֻ��һ��ֱ��ǰ��Ԫ�أ�
		�������һ��Ԫ��an�⣬ÿһ��Ԫ������ֻ��һ��ֱ�Ӻ��Ԫ�ء�
		����Ԫ��֮��Ĺ�ϵ��һ��һ�Ĺ�ϵ��

	Operation
		InitList(&L)����ʼ��������һ���յ����Ա�L,�����ڴ�ռ䡣
		DestroyList(&L)�����ٲ������������Ա����ͷ����Ա�L��ռ�õ��ڴ�ռ䡣

		ListInsert(&L,i,e)������������ڱ�L�еĵ�i��λ���ϲ���ָ��Ԫ��e��
		ListDelete(&l,i,&e)��ɾ��������ɾ����L�е�i��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ��

		LocateElem(L,e)����ֵ���Ҳ������ڱ�L�в��Ҿ��и����ؼ���ֵ��Ԫ�ء�
		GetElem(L,i)����λ���Ҳ�������ȡ��L�е�i��λ�õ�Ԫ�ص�ֵ��
		�������ò�����
		Length(L):������������Ա�L�ĳ��ȣ���L������Ԫ�صĸ�����
		PrintList(L):�����������ǰ��˳��������Ա�L������ֵ��
		Emrty(L):�пղ�������LΪ�ձ��򷵻�true,���򷵻�false��

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