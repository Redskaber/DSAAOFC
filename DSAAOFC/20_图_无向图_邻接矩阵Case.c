#include <stdio.h>
#include <stdlib.h>
#include "20_ͼ_����ͼ_�ڽӾ����ʵ��.h"


/*
	ͼ_����ͼ_�ڽӾ���CASE:
*/

int start_undirectedGraph_case()
{
	UGraph ugp;
	createUGraphInit(&ugp,10,16);
	printf("%d %d\n", ugp.vexNum,ugp.arcNum);

	//printArcArr(&ugp);
	//printVexArr(&ugp);

	int inInd = -1;
	inInd = vertexInGraph(&ugp, 3);
	printf("inInd:%d\n",inInd);
	int cout = 0;
	cout = vertexDgree(&ugp, 3);
	printf("cout:%d\n", cout);
	depthFirstSearch(&ugp);

	breadthFirstSearch(&ugp);


	// printf("ugp.vexNum:%d ugp.arcNum:%d\n", ugp.vexNum, ugp.arcNum);

	return 0;
}