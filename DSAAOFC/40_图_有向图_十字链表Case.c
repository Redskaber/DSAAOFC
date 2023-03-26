#include<stdio.h>
#include<stdlib.h>
#include "40_图_有向图_十字链表的实现.h"


int start_CrossLinkelist_Graph_case()
{
	CLGraph clgp;
	int vexArr[4] = {11,22,33,44};
	int vexArr2[6] = {11,22,33,44,55,66};
	int vexArr3[11] = {13,21,32,24,15,56,32,91,11,9};
	int relaArr[4][4] = {
		{65535, 1,    3,	 65535},					// OUT
		{3,     65535,3,		 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},
	};
	// IN

	int relaArr2[6][6] = {
	{65535,		5, 65535,	 15, 65535, 65535},			// OUT
	{10,    65535,    20, 65535,    20, 65535},
	{65535,    15, 65535,    15, 65535,	65535},
	{10,	65535,    10, 65535,    15,	    5},
	{25,	    5,    15, 65535, 65535,     5},
	{65535, 65535, 65535,     5,    10, 65535},
	};

	// CrossLinkGraphInit(&clgp, 4, vexArr, relaArr);
	CrossLinkGraphInit(&clgp, 6, vexArr2, relaArr2);
	clgp.printVexEdgeSet(&clgp);
	clgp.depthFirstSearch(&clgp, 0);
	clgp.breadthFirstSearch(&clgp, 0);
	
	int vexInNum	= clgp.vertexInedgeNumber(&clgp, 0);
	int vexOutNum	= clgp.vertexOutedgeNumber(&clgp, 0);
	printf("vexInNum:%d, vexOutNum:%d\n", vexInNum, vexOutNum);
	clgp.MinimumSpanTree_Prim(&clgp, 0);
	clgp.MinimumSpanTree_Kruskal(&clgp);

	destroyCrossGraph(&clgp);
	printf("clgp->vexNum:%d, clgp->arcNum:%d\n", clgp.vexNum, clgp.arcNum);

	return 0;
}