#include<stdio.h>
#include "02_动态顺序表的构建.h"


int start_dynamic_linker()
{
	printf("*******************************《DSeqListInit》*********************************\n");
	DSEQL DL1;
	DSEQL DL2;

	ElemType InitArray[] = {
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
		0,1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,0,
	};
	int InitCount = 10;
	Rstatus InitStatus1 = DSeqListInit(&DL1, _initcode.AUTO);
	Rstatus InitStatus2 = DSeqListInit(&DL2, _initcode.USE_ARRAY,InitArray,InitCount);

	printf("InitStatus1:%d\n", InitStatus1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);
	DSeqListPrint(&DL1);

	printf("InitStatus2:%d\n", InitStatus2);
	printf("DL2.length:%zd\n", DL2.length);
	printf("DL2.capacity:%zd\n", DL2.capacity);
	DSeqListPrint(&DL2);

	printf("******************************《DSeqListPushBalk》********************************\n");
	ElemType NewElem = 10;
	DSeqListPrint(&DL2);
	DSeqListPushBalk(&DL2, NewElem);
	DSeqListPrint(&DL2);
	printf("DL2.length:%zd\n", DL2.length);
	printf("DL2.capacity:%zd\n", DL2.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListPushBalk(&DL2, ++NewElem);

	DSeqListPrint(&DL2);
	printf("DL2.length:%zd\n", DL2.length);
	printf("DL2.capacity:%zd\n", DL2.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListPushBalk(&DL2, ++NewElem);

	DSeqListPrint(&DL2);
	printf("DL2.length:%zd\n", DL2.length);
	printf("DL2.capacity:%zd\n", DL2.capacity);

	printf("******************************《DSeqListPushFront》********************************\n");
	DSeqListPrint(&DL1);
	DSeqListPushFront(&DL1, NewElem);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListPushFront(&DL1, ++NewElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListPushFront(&DL1, ++NewElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListInsert》********************************\n");
	Index insertInd = 1;
	ElemType insertElem = 100;
	DSeqListInsert(&DL1, insertInd, insertElem);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListInsert(&DL1, --insertInd, ++insertElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListInsert(&DL1, ++insertInd, ++insertElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListToIndRemove》********************************\n");
	Index reInd = 1;
	DSeqListToIndRemove(&DL1,reInd);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++)	DSeqListToIndRemove(&DL1, ++reInd);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++)	DSeqListToIndRemove(&DL1, ++reInd);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListToElemRemove》********************************\n");
	ElemType RElem = 100;
	DSeqListToElemRemove(&DL1, RElem);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListToElemRemove(&DL1, ++RElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListToElemRemove(&DL1, ++RElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListToIndReplace》********************************\n");
	Index rind = 0;
	DSeqListToIndReplace(&DL1, rind, RElem);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListToIndReplace(&DL1, ++rind, ++RElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListToElemReplace》********************************\n");
	ElemType oElem = 200;
	ElemType rElem = 1000;
	DSeqListToElemReplace(&DL1, oElem, rElem);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListToElemReplace(&DL1, ++oElem, ++rElem);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListIndPop》********************************\n");
	ElemType pElem = 100;
	Index pind = 0;
	DSeqListIndPop(&DL1, pind);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	for (size_t num = 0; num < 50; num++) DSeqListIndPop(&DL1, ++pind);

	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListIndPopAll》********************************\n");
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);
	DSeqListIndPopAll(&DL1);
	DSeqListPrint(&DL1);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);

	printf("******************************《DSeqListDestroy》********************************\n");
	DSeqListDestroy(&DL1);
	DSeqListDestroy(&DL2);
	printf("DL1.length:%zd\n", DL1.length);
	printf("DL1.capacity:%zd\n", DL1.capacity);
	printf("DL2.length:%zd\n", DL2.length);
	printf("DL2.capacity:%zd\n", DL2.capacity);

	return 0;
}
