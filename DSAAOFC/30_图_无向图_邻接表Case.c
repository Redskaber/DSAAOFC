#include <stdio.h>
#include <stdlib.h>
#include "30_图_无向图_邻接表的实现.h"


int start_adjacencyTable_Graph_case()
{
	AGraph agp;
	int vexArr[6] = {11,22,33,44,55,66};
	int vexRelaArr[4][4] = {
		{0,1,1,1},
		{1,0,1,0},
		{1,1,0,1},
		{1,0,1,0},
	};
	int vexRelaArr2[6][6] = {
	{0, 1, 1, 1, 1, 0},
	{1, 0, 1, 0, 1, 1},
	{1, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 1},
	{0, 1, 1, 0, 1, 0},
	};
	adjGraphInit(&agp, 6, vexArr, vexRelaArr2);
	printAGraph(&agp);
	printRelaArr(vexRelaArr2);
	depthFirstSearch(&agp, 11);
	depthFirstSearch(&agp, 22);
	depthFirstSearch(&agp, 33);
	depthFirstSearch(&agp, 44);
	depthFirstSearch(&agp, 55);
	depthFirstSearch(&agp, 66);

	destroyAGraph(&agp);


	return 0;
}