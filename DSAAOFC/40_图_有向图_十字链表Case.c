#include<stdio.h>
#include<stdlib.h>
#include "40_图_有向图_十字链表的实现.h"


int start_CrossLinkelist_Graph_case()
{
	CLGraph clgp;
	int vexArr[4] = {11,22,33,44};
	int vexArr2[6] = {11,22,33,44,55,66};
	int relaArr[4][4] = {
		{65535, 1,    3,	 65535},					// OUT
		{3,     65535,3,		 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},
	};
	// IN

	int relaArr2[6][6] = {
	{65535, 1,    65535,	  2, 65535, 65535},			// OUT
	{3,     65535,    3,  65535,     1, 65535},
	{65535,     1,    65535,  4, 65535,	65535},
	{4,		65535,     4, 65535,     1,	    3},
	{3,		    1,     4, 65535, 65535,     3},
	{65535, 65535, 65535,     3,     1, 65535},
	};

	// CrossLinkGraphInit(&clgp, 4, vexArr, relaArr);
	CrossLinkGraphInit(&clgp, 6, vexArr2, relaArr2);
	clgp.printVexEdgeSet(&clgp);
	clgp.depthFirstSearch(&clgp, 0);
	clgp.breadthFirstSearch(&clgp, 0);
	destroyCrossGraph(&clgp);
	printf("clgp->vexNum:%d, clgp->arcNum:%d\n", clgp.vexNum, clgp.arcNum);

	return 0;
}