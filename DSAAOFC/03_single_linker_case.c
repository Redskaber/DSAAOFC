/*



*/

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
#include "03_单向链表的构建.h"

int start_single_linker()
{
	printf("*********************************《SingleLinkerInit》*********************************\n");
	SingleLinker slp;
	SingleLinkerInit(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	printf("************************************《appendNode》************************************\n");
	appendNode(&slp, 100);
	appendNode(&slp, 200);
	appendNode(&slp, 300);
	appendNode(&slp, 400);
	appendNode(&slp, 500);

	SinLinNodePrint(&slp);

	printf("*************************************《addNode》**************************************\n");
	addNode(&slp, 100);
	addNode(&slp, 200);
	addNode(&slp, 300);
	addNode(&slp, 400);

	SinLinNodePrint(&slp);

	printf("***********************************《findNode》***************************************\n");
	SingleNode* cNode = createNode(1000);
	SingleNode* hN = _findNode(&slp, slp.headNode);
	SingleNode* eN = _findNode(&slp, slp.endNode);
	SingleNode* nN = _findNode(&slp, cNode);
	if (hN != NULL) printf("hN.data:%d, hN.next:%p\n", hN->data, hN->next);
	if (eN != NULL) printf("eN.data:%d, eN.next:%p\n", eN->data, eN->next);
	if (nN != NULL) printf("nN.data:%d, nN.next:%p\n", nN->data, nN->next);
	destroyNode(cNode);
	printf("\n");
	SingleNode* fh =  findNode(&slp, 0);
	SingleNode* f1 =  findNode(&slp, 100);
	SingleNode* f2 =  findNode(&slp, 200);
	SingleNode* f3 =  findNode(&slp, 300);
	SingleNode* fe =  findNode(&slp, 400);
	if (fh != NULL) printf("fh.data:%d, fh.next:%p\n", fh->data, fh->next);
	if (f1 != NULL) printf("f1.data:%d, f1.next:%p\n", f1->data, f1->next);
	if (f2 != NULL) printf("f2.data:%d, f2.next:%p\n", f2->data, f2->next);
	if (f3 != NULL) printf("f3.data:%d, f3.next:%p\n", f3->data, f3->next);
	if (fe != NULL) printf("fe.data:%d, fe.next:%p\n", fe->data, fe->next);

	printf("***********************************《insertNode》*************************************\n");
	insertNode(&slp, 100, 110);
	// insertNode(&slp,1000,110);	assert(findNode !=NULL);
	insertNode(&slp, 0, 120);		
	insertNode(&slp, 0, 130);
	insertNode(&slp, 400, 140);
	insertNode(&slp, 500, 150);
	SinLinNodePrint(&slp);

	printf("***********************************《removeNode》*************************************\n");
	removeNode(&slp, 100);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	removeNode(&slp, 150);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	removeNode(&slp, 130);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	printf("***********************************《rfrontNode》*************************************\n");
	rfrontNode(&slp);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	rfrontNode(&slp);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);
	printf("************************************《popNode》***************************************\n");
	popNode(&slp);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	popNode(&slp);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	printf("********************************《replaceNodeVal》************************************\n");
	replaceNodeVal(&slp,100,2000);
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);

	Rstatus status = replaceNodeVal(&slp, 1000, 2000);		// not'n return  NULL
	SinLinNodePrint(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);
	if (status) SinLinNodePrint(&slp);
	printf("********************************《SingleLinkerIsEmrty》************************************\n");
	Rstatus r = SingleLinkerIsEmrty(&slp);
	printf("%d\n",r);

	printf("********************************《SingleLinkerDestroy》************************************\n");
	SingleLinkerDestroy(&slp);
	printf("%d %d %zd\n", slp.headNode->data, slp.endNode->data, slp.length);
	// SinLinNodePrint(&slp); error

	return 0;
}
