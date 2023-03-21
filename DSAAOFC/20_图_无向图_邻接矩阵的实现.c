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

void createUGraphInit(UGraph* ugp, int vexNum, int arcNum)
{
	assert(vexNum <= MaxVertexNum);
	int maxArcNum = (vexNum * (vexNum - 1)) / 2;
	if (arcNum > maxArcNum) arcNum = maxArcNum;

	memset(ugp, 0, sizeof(UGraph));
	ugp->vexNum = vexNum;
	ugp->arcNum = arcNum;

	/*顶点表：默认从0开始*/
	for (int i = 0; i < ugp->vexNum; i++) ugp->vexArr[i] = i;
	/*边表：单点达极数*/
	int arcTemp = arcNum;
	for (int row = 0; row < ugp->vexNum; row++)
	{
		for (int col = 0; col < ugp->vexNum; col++) 
		{
			if (row == col) ugp->edgeArr[row][col] = notex;		// 对角线
			if (row != col)
			{
				if (ugp->edgeArr[col][row]) ugp->edgeArr[row][col] = exist;		// 对角线对折
				else
				{
					if (arcTemp-- > 0) ugp->edgeArr[row][col] = exist;			// 新的边
					else ugp->edgeArr[row][col] = notex;			
				}
			}
			printf("%d ", ugp->edgeArr[row][col]);
		}
		printf("\n");
	}
}

int vertexInGraph(UGraph* ugp, int vertex)
{
	for (int i = 0; i < ugp->vexNum; i++)
	{
		if (ugp->vexArr[i] == vertex) return i;		// row for
	}
	return -1;
}

int vertexDgree(UGraph* ugp, int vertex)
{
	int cout = 0;
	int inInd = vertexInGraph(ugp, vertex);
	if (inInd != -1)
	{
		for (int i = 0; i < ugp->vexNum; i++)		// col for
		{
			if (ugp->edgeArr[inInd][i] != notex) cout++;
		}
	}
	return cout;
}

void visit(UGraph* ugp, int vexInd)
{
	printf("%d ",ugp->vexArr[vexInd]);
}

int depthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//求图G中顶点v的第一个邻接点，若有则返回顶点下标，否则返回-1。
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*边存在并且是未被遍历过的*/
		if (ugp->edgeArr[row][col] != notex && !depthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && depthvisited[col] && vexInd > 1) depthfirstNeihbor(ugp, vexInd - 1); /*边界回退*/
	}

	return -1;
}

int depthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
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

void DFS(UGraph* ugp, int vexInd)
{
	/*
	首先访问图中某一起始顶点vexInd，然后由vexInd出发，访问与vexInd邻接且未被访问的任一顶点nextVexInd，再访问与nextVexInd邻接且未被访问的任一顶点
	…重复上述过程。
	*/
	int nextVexInd;
	visit(ugp, vexInd);
	depthvisited[vexInd] = true;
	for (nextVexInd = depthfirstNeihbor(ugp, vexInd); nextVexInd > 0; nextVexInd = depthnextNeighbor(ugp, vexInd, nextVexInd)) {
		if (!depthvisited[nextVexInd]) DFS(ugp, nextVexInd); 		//nextVexInd为vexInd的尚未访问的邻接顶点	

	}
}

void depthFirstSearch(UGraph* ugp)
{
	/*图的深度优先算法，类似于树的先序遍历
				0
			1		2
		3	4		5	6	
		=>0,1,3,4,2,5,6
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;
	memset(depthvisited, false, sizeof(depthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; ++vexInd) if (!depthvisited[vexInd]) DFS(ugp, vexInd);	// 访问第一个顶点
	printf("\n");
}


void queueInit(Queue* queue)
{
	memset(queue->queue, -1, sizeof(queue->queue));
	queue->length = 0;
}

void enqueue(Queue* queue, int data)
{
	queue->queue[queue->length++] = data;
}

void unqueue(Queue* queue, int ind)
{
	for (int i = 0; i < queue->length; i++)
	{
		if (i == queue->length - 1) queue->queue[i] = -1;
		else if (i >= ind) queue->queue[i] = queue->queue[i + 1];
	}
	queue->length--;
}

bool queueEmpty(Queue* queue)
{
	return queue->length == 0;
}

void printQueue(Queue* queue)
{
	for (int i = 0; i < queue->length; i++)
	{
		printf("%d ",(int)queue->queue[i]);
	}
	printf("\n");
}

int breadthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//求图G中顶点v的第一个邻接点，若有则返回顶点下标，否则返回-1。
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*边存在并且是未被遍历过的*/
		if (ugp->edgeArr[row][col] != notex && !breadthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && breadthvisited[col] && vexInd > 1) breadthfirstNeihbor(ugp, vexInd - 1); /*边界回退*/
	}

	return -1;
}

int breadthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
{
	//假设图G中顶点vexInd是顶点nextVex的一个邻接点，返回除vexInd外顶点nextVex		
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		int edgeEx = ugp->edgeArr[row][col];	// 由顶点vex所邻接的所有顶点集合
		if (edgeEx == exist && ugp->vexArr[vexInd] != ugp->vexArr[nextInd] && !breadthvisited[col]) return col;
	}
	return  -1;
}


void breadthFirstSearch(UGraph* ugp)
{
	/* 图的广度优先遍历算法，类似于数的层级遍历
				0
			1		2
		3	4		5	6	
		=> 0,1,2,3,4,5,6
		queue
			v0 v1 v2 v3
		v0	0  1  1	 1
		v1	1  0  1	 1
		v2	1  1  0	 0
		v3	1  1  0	 0

		v0 -> queue[1,2,3] && visit(v0)  && breadthvisited[v0]
		for vex in (queue) -> breadthvisited[vex] && if(!breadthvisited[vex]) queue 
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;

	Queue queue;
	queueInit(&queue);
	memset(breadthvisited, false, sizeof(breadthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; vexInd++)
	{
		if (!breadthvisited[vexInd])
		{
			visit(ugp, vexInd);				//访问顶点
			breadthvisited[vexInd] = true;	// 标记
			enqueue(&queue, vexInd);	//将此顶点入队列
			//若当前队列不为空
			while (!queueEmpty(&queue)) {
				unqueue(&queue, vexInd);	//顶点i出队列
				for (int nextVexInd = breadthfirstNeihbor(ugp, vexInd); nextVexInd >= 0; nextVexInd = breadthnextNeighbor(ugp, vexInd, nextVexInd)) {
					if (!breadthvisited[nextVexInd])
					{
						visit(ugp, nextVexInd);				//访问顶点j
						breadthvisited[nextVexInd] = true;	//访问标记
						enqueue(&queue, nextVexInd);						//顶点j入队列
					}

				}
			}
		}
	};
	//printQueue(&queue);
	//printf("length:%d\n",queue.length);
}



void printArcArr(UGraph* ugp)
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

void printVexArr(UGraph* ugp)
{
	for (int i = 0; i < ugp->vexNum; i++) printf("%d ",ugp->vexArr[i]);
	printf("\n");
}