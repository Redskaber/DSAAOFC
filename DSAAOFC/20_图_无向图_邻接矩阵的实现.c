#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "20_图_无向图_邻接矩阵的实现.h"

/*
	图_无向图的邻接矩阵实现文件

	G(V,E)		// 图的顶点一定要有(V>0),而图的边可以没有(E>=0)
		- INIT
			-> Vertex		>  0
			-> Edge			>= 0

		无向图无权重的初始化
		这里外部传入图的顶点数与边数作为参数进行创建图
		:int verNum  顶点数
		:int arcNum  边数		 边数超过最大链接默认选择最大链接（(VerNum-1)*VerNum）/2
		1 - (0*1)/2 = 0
		2 - (1*2)/2 = 1
		3 - (2*3)/2 = 3
		4 - (3*4)/2 = 6
		n - (n-1*n)/2
*/

static bool depthvisited[MaxVertexNum];	//访问标记数组
static bool breadthvisited[MaxVertexNum];	//访问标记数组

static int vertexDgree(UGraph* ugp, int vertex);
static int vertexInGraph(UGraph* ugp, int vertex);
static void depthFirstSearch(UGraph* ugp);
static void printArcArr(UGraph* ugp);
static void printVexArr(UGraph* ugp);
static void breadthFirstSearch(UGraph* ugp);
static void MiniSpanTree_Prim(UGraph* ugp);



static void stackInit(Stack* stack)
{
	memset(stack->stack, -1, sizeof(stack->stack));
	stack->length = 0;
}

static void enstack(Stack* stack, int data)
{
	stack->stack[stack->length++] = data;
}

static void unstack(Stack* stack, int ind)
{
	for (int i = 0; i < stack->length; i++)
	{
		if (i == stack->length - 1) stack->stack[i] = -1;
		else if (i >= ind) stack->stack[i] = stack->stack[i + 1];
	}
	stack->length--;
}

static bool stackEmpty(Stack* stack)
{
	return stack->length == 0;
}

static void printstack(Stack* stack)
{
	for (int i = 0; i < stack->length; i++)
		printf("%d ", (int)stack->stack[i]);
	printf("\n");
}


void createUGraphInit(UGraph* ugp, int vexNum, int vexArr[], int (*vexRelaArr)[VexRelaArrNum])
{
	assert(vexNum <= MaxVertexNum);
	memset(ugp, 0, sizeof(UGraph));
	ugp->vexNum = vexNum;
	ugp->arcNum = 0;

	/*顶点表：默认从0开始*/
	for (int i = 0; i < ugp->vexNum; i++) ugp->vexArr[i] = i;
	/*边表数*/
	int vexweight = 0;
	for (int rearInd = 0; rearInd < ugp->vexNum; rearInd++)
	{
		for (int frontInd = 0; frontInd < ugp->vexNum; frontInd++)
		{
			vexweight = vexRelaArr[rearInd][frontInd];
			ugp->edgeArr[rearInd][frontInd] = vexweight;
			if (vexweight) ugp->arcNum++;
		}
	}
	ugp->arcNum				= ugp->arcNum / 2;
	ugp->printArcArr		= printArcArr;
	ugp->printVexArr		= printVexArr;
	ugp->vertexInGraph		= vertexInGraph;
	ugp->vertexDgree		= vertexDgree;
	ugp->depthFirstSearch	= depthFirstSearch;
	ugp->breadthFirstSearch = breadthFirstSearch;
	ugp->MiniSpanTree_Prim	= MiniSpanTree_Prim;
}

static int vertexInGraph(UGraph* ugp, int vertex)
{
	for (int i = 0; i < ugp->vexNum; i++)
		if (ugp->vexArr[i] == vertex) return i;		// row for
	return -1;
}

static int vertexDgree(UGraph* ugp, int vertex)
{
	int cout = 0;
	int inInd = vertexInGraph(ugp, vertex);
	if (inInd != -1)
	{
		for (int i = 0; i < ugp->vexNum; i++)
			if (ugp->edgeArr[inInd][i] != notex) cout++;
	}
	return cout;
}

static void visit(UGraph* ugp, int vexInd)
{
	printf("%d ",ugp->vexArr[vexInd]);
}

static int depthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//求图G中顶点v的第一个邻接点，若有则返回顶点下标，否则返回-1。
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*边存在并且是未被遍历过的*/
		if (ugp->edgeArr[row][col] != notex && !depthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && depthvisited[col] && vexInd > 1) 
			depthfirstNeihbor(ugp, vexInd - 1); /*边界回退*/
	}

	return -1;
}

static int depthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
{
	//假设图G中顶点vexInd是顶点nextVex的一个邻接点，返回除vexInd外顶点nextVex	
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		int edgeEx = ugp->edgeArr[row][col];	// 由顶点vex所邻接的所有顶点集合
		if (edgeEx == exist && ugp->vexArr[vexInd]!= ugp->vexArr[nextInd] && !depthvisited[col]) return col;
	}
	return  -1;
}

static void DFS(UGraph* ugp, int vexInd)
{
	/*
	首先访问图中某一起始顶点vexInd，然后由vexInd出发，访问与vexInd邻接且未被访问的任一顶点nextVexInd，再访问与nextVexInd邻接且未被访问的任一顶点
	…重复上述过程。
	*/
	int nextVexInd;
	visit(ugp, vexInd);
	depthvisited[vexInd] = true;

	nextVexInd = depthfirstNeihbor(ugp, vexInd);
	for (nextVexInd; nextVexInd > 0; nextVexInd) {
		if (!depthvisited[nextVexInd]) DFS(ugp, nextVexInd); 		//nextVexInd为vexInd的尚未访问的邻接顶点	
		nextVexInd = depthnextNeighbor(ugp, vexInd, nextVexInd);
	}
}

static void depthFirstSearch(UGraph* ugp)
{
	/*图的深度优先算法，类似于树的先序遍历
				0
			1		2
		3	4		5	6	
		=>0,1,3,4,2,5,6
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;
	memset(depthvisited, false, sizeof(depthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; ++vexInd) 
		if (!depthvisited[vexInd]) DFS(ugp, vexInd);	// 访问第一个顶点
	printf("\n");
}

static int breadthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//求图G中顶点v的第一个邻接点，若有则返回顶点下标，否则返回-1。
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*边存在并且是未被遍历过的*/
		if (ugp->edgeArr[row][col] != notex && !breadthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && breadthvisited[col] && vexInd > 1) 
			breadthfirstNeihbor(ugp, vexInd - 1); /*边界回退*/
	}

	return -1;
}

static int breadthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
{
	//假设图G中顶点vexInd是顶点nextVex的一个邻接点，返回除vexInd外顶点nextVex		
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		int edgeEx = ugp->edgeArr[row][col];	// 由顶点vex所邻接的所有顶点集合
		if (edgeEx == exist && ugp->vexArr[vexInd] != ugp->vexArr[nextInd] && !breadthvisited[col]) 
			return col;
	}
	return  -1;
}

static void breadthFirstSearch(UGraph* ugp)
{
	/* 图的广度优先遍历算法，类似于数的层级遍历
				0
			1		2
		3	4		5	6	
		=> 0,1,2,3,4,5,6
		stack
			v0 v1 v2 v3
		v0	0  1  1	 1
		v1	1  0  1	 1
		v2	1  1  0	 0
		v3	1  1  0	 0

		v0 -> stack[1,2,3] && visit(v0)  && breadthvisited[v0]
		for vex in (stack) -> breadthvisited[vex] && if(!breadthvisited[vex]) stack 
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;
	int nextVexInd;

	Stack stack;
	stackInit(&stack);
	memset(breadthvisited, false, sizeof(breadthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; vexInd++)
	{
		if (!breadthvisited[vexInd])
		{
			visit(ugp, vexInd);				// 访问顶点
			breadthvisited[vexInd] = true;	// 标记
			enstack(&stack, vexInd);		// 将此顶点入队列

			while (!stackEmpty(&stack)) {	// 若当前队列不为空

				unstack(&stack, vexInd);	// 顶点i出队列

				nextVexInd = breadthfirstNeihbor(ugp, vexInd);
				for (nextVexInd; nextVexInd >= 0; nextVexInd) {
					if (!breadthvisited[nextVexInd])
					{
						visit(ugp, nextVexInd);					// 访问顶点
						breadthvisited[nextVexInd] = true;		// 访问标记
						enstack(&stack, nextVexInd);			//顶点j入队列
					}
					nextVexInd = breadthnextNeighbor(ugp, vexInd, nextVexInd);
				}
			}
		}
	}
	printf("\n");
}


/*Prim算法生成最小生成树*/
static void MiniSpanTree_Prim(UGraph* ugp) 
{
	int min, i, j, k;
	int adjvex[MaxVertexNum];		
	int lowcost[MaxVertexNum];	

	lowcost[0] = 0;			//初始化第一个权值为0，即v0加入生成树 //lowcost的值为0，在这里就是此下标的顶点已经加入生成树
	adjvex[0] = 0;			//初始化第一个顶点下标为0

	for (i = 1; i < ugp->vexNum; i++) 
	{
		lowcost[i] = ugp->edgeArr[0][i];		//将v0顶点与之组成边的权值存入数组
		adjvex[i] = 0;							//初始化都为v0的下标
	}
	for (i = 1; i < ugp->vexNum; i++) 
	{
		min = WeightMax;					//初始化最下权值为∞，通常设置一个不可能的很大的数字
		j = 1; k = 0;

		//循环全部顶点
		while (j < ugp->vexNum) 
		{
			//如果权值不为0且权值小于min
			if (lowcost[j] != 0 && lowcost[j] < min) 
			{
				min = lowcost[j];		//则让当前权值成为最小值
				k = j;					//将当前最小值的下标存入k
			}
			j++;
		}
		printf("(%d, %d) ", adjvex[k], k);	//打印当前顶点边中权值的最小边
		for (j = 1; j < ugp->vexNum; j++) 
		{
			//若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
			if (lowcost[j] != 0 && ugp->edgeArr[k][j] < lowcost[j]) 
			{
				lowcost[j] = ugp->edgeArr[k][j];		//将较小权值存入lowcost
				adjvex[j] = k;							//将下标为k的顶点存入adjvex
			}
		}
	}
}



static void printArcArr(UGraph* ugp)
{
	for (int row = 0; row < ugp->vexNum; row++)
	{
		for (int col = 0; col < ugp->vexNum; col++)
		{
			printf("%d ", ugp->edgeArr[row][col]);
		}
		printf("\n");
	}
}

static void printVexArr(UGraph* ugp)
{
	for (int i = 0; i < ugp->vexNum; i++) printf("%d ",ugp->vexArr[i]);
	printf("\n");
}