#include <stdio.h>
#include <stdlib.h>
#include "20_图_无向图_邻接矩阵的实现.h"


/*
	图_无向图_邻接矩阵CASE:
*/

int start_undirectedGraph_case()
{
	UGraph ugp;

	int vexArr[10] = { 11, 22, 33, 44, 55, 66, 77, 88, 99, 00 };
	int vexEdgeRelaArr[10][10] = {
		{0,	2, 2, 6, 2, 8, 0, 4, 0, 2},
		{2,	0, 0, 2, 0, 0, 2, 0, 2, 0},
		{2,	0, 0, 4, 6, 4, 0, 2, 0, 4},
		{6,	2, 4, 0, 6, 0, 2, 4, 0, 2},
		{2,	0, 6, 6, 0, 8, 0, 4, 0, 0},
		{8,	0, 4, 0, 8, 0, 6, 2, 6, 8},
		{0,	2, 0, 2, 0, 6, 0, 6, 0, 2},
		{4,	0, 2, 4, 4, 2, 6, 0, 8, 0},
		{0,	2, 0, 0, 0, 6, 0, 8, 0, 2},
		{2,	0, 4, 2, 0, 8, 2, 0, 2, 0},
	};
	createUGraphInit(&ugp,10, vexArr, vexEdgeRelaArr);
	printf("%d %d\n", ugp.vexNum,ugp.arcNum);

	//printArcArr(&ugp);
	//printVexArr(&ugp);

	int inInd = -1;
	inInd = ugp.vertexInGraph(&ugp, 3);
	printf("inInd:%d\n",inInd);
	int cout = 0;
	cout = ugp.vertexDgree(&ugp, 3);
	printf("cout:%d\n", cout);
	ugp.depthFirstSearch(&ugp);

	ugp.breadthFirstSearch(&ugp);
	ugp.MiniSpanTree_Prim(&ugp);
	// printf("ugp.vexNum:%d ugp.arcNum:%d\n", ugp.vexNum, ugp.arcNum);

	return 0;
}