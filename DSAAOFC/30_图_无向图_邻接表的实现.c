#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "30_图_无向图_邻接表的实现.h"



/*
	图-无向图邻接表
*/

static int depthvisitCout = 0;
static bool depthvisited[MaxVexNum];		// 深度遍历工具
static bool breadthvisited[MaxVexNum];		// 广度遍历工具
static void printVexNodeLink(AGraph* agp, int adjInd);


void queueInit(Queue* queue)
{
	memset(queue->queue, -1, sizeof(queue->queue));
	queue->length = 0;
}

void enqueue(Queue* queue, int ind)
{
	queue->queue[queue->length++] = ind;
}

void unqueue(Queue* queue)
{
	queue->queue[queue->length-- - 1] = -1;
}


VertexNode* createVertexNode(VertexType data)
{
	VertexNode* newVertexNode = NULL;
	newVertexNode = (VertexNode*)malloc(sizeof(VertexNode));
	assert(newVertexNode != NULL);
	newVertexNode->data = data;
	newVertexNode->firstEdge = NULL;
	return newVertexNode;
}


EdgeNode* createEdgeNode(int adjVexInd)
{
	EdgeNode* newEdgeNode = NULL;
	newEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
	assert(newEdgeNode != NULL);
	newEdgeNode->adjVexInd = adjVexInd;
	newEdgeNode->next = NULL;
	return newEdgeNode;
}

void destroyEdgeNode(EdgeNode* tempnextEdge)
{
	if (tempnextEdge)
	{
		destroyEdgeNode(tempnextEdge->next);
		free(tempnextEdge);
	}
}


void destroyAGraph(AGraph* agp)
{
	VertexNode* tempVex;
	EdgeNode* tempEdge;

	for (int i = 0; i < agp->vexNum; i++) 
	{
		tempVex = agp->adjlist[i];
		tempEdge = tempVex->firstEdge;
		if(tempEdge->next) destroyEdgeNode(tempEdge->next);
		free(tempVex);
	}
}


void adjGraphInit(AGraph* agp, int vexNum, VertexType* vexArr, VertexType (*vexRelaArr)[vertexInNum] )
{
	/*
		AGraph*    agp:	 邻接表
		int		vexNum:	 顶点数
		int**  vexRela:	 边图
		{
			{0,1,1,1},
			{1,0,1,0},
			{1,1,0,1},
			{1,0,1,0},
		}
	*/
	assert(vexNum < MaxVexNum && vexNum > 0);
	agp->vexNum = vexNum;
	agp->arcNum = 0;

	/*顶点表：data, firstEdge*/
	VertexNode* tempVex;
	memset(agp->adjlist, 0, sizeof(VertexNode*));
	for (int adjVexInd = 0; adjVexInd < vexNum; adjVexInd++)
	{
		tempVex = createVertexNode(vexArr[adjVexInd]);
		agp->adjlist[adjVexInd] = tempVex;
	}

	/*边表：VexInd, next, + arcNum*/
	for (int adjVexInd = 0; adjVexInd < vexNum; adjVexInd++)		// [v0,v1,v2,v3,...]
	{
		tempVex = agp->adjlist[adjVexInd];
		for (int vexrelaInd = 0; vexrelaInd < vexNum; vexrelaInd++)
		{
			if (adjVexInd == vexrelaInd) continue;
			if (vexRelaArr[adjVexInd][vexrelaInd])		// 存在邻接顶点!= 0
			{
				EdgeNode* newEdge;
				EdgeNode* tempfirstEdge;
				VertexNode* adjVexTemp;
				
				newEdge = createEdgeNode(vexrelaInd);
				adjVexTemp = agp->adjlist[adjVexInd];

				if (adjVexTemp->firstEdge)
				{
					tempfirstEdge = adjVexTemp->firstEdge;
					newEdge->next = tempfirstEdge;
				}
				adjVexTemp->firstEdge = newEdge;
				agp->arcNum++;			// 2e
			}
		}
	}
	agp->arcNum = agp->arcNum / 2;
	queueInit(&queue);
}




int vexInGraph(AGraph* agp, VertexType data)
{
	for (int adjInd = 0; adjInd < agp->vexNum; adjInd++)
	{
		if (agp->adjlist[adjInd]->data == data) return adjInd;
	}
	return -1;
}

void initdepthtool()
{
	memset(depthvisited, false, sizeof(depthvisited));
	depthvisitCout = 0;
}

void visit(AGraph* agp, int adjInd)
{
	printf("%d ", agp->adjlist[adjInd]->data);
	depthvisited[adjInd] = true;
	depthvisitCout++;
}


int getVertexInd(AGraph* agp, VertexNode* startNode)
{
	for (int adjInd = 0; adjInd < agp->vexNum; adjInd++)
	{
		if (agp->adjlist[adjInd] == startNode) return adjInd;
	}
	return -1;
}


int depthFirstNeighbor(AGraph* agp, EdgeNode* tempEdgeNode)
{
	int nextInd;
	nextInd = tempEdgeNode->adjVexInd;
	if (depthvisited[nextInd] != true)
	{
		enqueue(&queue, nextInd);
		return nextInd;
	}		
	else
	{
		tempEdgeNode = tempEdgeNode->next;
		if (depthvisitCout == agp->vexNum) return -1;
		if (!tempEdgeNode)
		{
			tempEdgeNode = agp->adjlist[queue.queue[queue.length - 1]]->firstEdge;		// queue 队列存储前遍历的顶点下标
			unqueue(&queue);
		}
		return depthFirstNeighbor(agp, tempEdgeNode);
	}
}


void DFS(AGraph* agp, int vexInd)
{
	/*访问此顶点的邻接顶点：获取第一个邻接顶点，访问后，找邻接顶点的邻接顶点*/
	EdgeNode* tempEdgeNode;

	visit(agp, vexInd);		
	tempEdgeNode = agp->adjlist[vexInd]->firstEdge;
	if (!tempEdgeNode) return;
	vexInd = depthFirstNeighbor(agp, tempEdgeNode);
	if (vexInd != -1) DFS(agp, vexInd);
}

void depthFirstSearch(AGraph* agp, VertexType startVex)
{
	/*
	无向图邻接表的深度优先遍历
	{
		{0,1,1,1},						   [11]
		{1,0,1,0},
		{1,1,0,1},					[22]		[44]
		{1,0,1,0},						 [33]
	}
	*/
	int adjInd;
	adjInd = vexInGraph(agp, startVex);
	assert(adjInd != -1);
	_depthFirstSearch(agp, adjInd);
}

void _depthFirstSearch(AGraph* agp, int adjInd)
{
	/*初始化深度遍历列表*/
	initdepthtool();
	if (adjInd != -1 && !depthvisited[adjInd]) DFS(agp, adjInd);		// 没有被访问过
	printf("\n");
}


void printVexNodeLink(AGraph* agp, int adjInd)
{
	VertexNode* tempVexNode;
	EdgeNode* tempEdgeNode;
	tempVexNode = agp->adjlist[adjInd];
	tempEdgeNode = tempVexNode->firstEdge;
	printf("tempEdgeNode: %d ", tempEdgeNode->adjVexInd);
	while (tempEdgeNode->next)
	{
		tempEdgeNode = tempEdgeNode->next;
		printf("%d ", tempEdgeNode->adjVexInd);
	}
	printf("\n");
}


void printAGraph(AGraph* agp)
{
	for (int i = 0; i < agp->vexNum; i++) printf("%d ", agp->adjlist[i]->data);
	printf("\n");
	printf("agp->vexNum:%d, agp->arcNum:%d\n", agp->vexNum, agp->arcNum);
}


void printRelaArr(VertexType(*vexRelaArr)[vertexInNum])
{
	for (int i = 0; i < vertexInNum; i++)
	{
		for (int j = 0; j < vertexInNum; j++) printf("%d ", vexRelaArr[i][j]);
		printf("\n");
	}

}


