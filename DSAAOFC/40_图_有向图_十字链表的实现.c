/* ͼ_����ͼ_ʮ�������ʵ�� */

/*
	G(V,E)
	 - V(G)		�����
	 - E(G)		�߱�
	 - ʮ�������ڽӱ������ڽӱ�)
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
#include "40_ͼ_����ͼ_ʮ�������ʵ��.h"




static void BFS(CLGraph* clgp, int vexInd, BVisited* breadthVisited);
static void depthFirstSearch(CLGraph* clgp, int vexInd);
static void breadthFirstSearch(CLGraph* clgp, int vexInd);
static int  vertexInedgeNumber(CLGraph* clgp, int vexInd);
static int  vertexOutedgeNumber(CLGraph* clgp, int vexInd);
static void MinimumSpanTree(CLGraph* clgp, int vexInd);
static void printVexEdgeSet(CLGraph* clgp);





static InEdge* createInEdge(EdgeType weight, int rearInd)
{
	InEdge* newInEdge = NULL;
	newInEdge = (InEdge*)malloc(sizeof(InEdge));
	assert(newInEdge != NULL);
	newInEdge->inWeight = weight;
	newInEdge->inVexInd = rearInd;
	newInEdge->next = NULL;
	return newInEdge;
}

static OutEdge* createOutEdge(EdgeType weight, int frontInd)
{
	OutEdge* newOutEdge = NULL;
	newOutEdge = (OutEdge*)malloc(sizeof(OutEdge));
	assert(newOutEdge != NULL);
	newOutEdge->outWeight = weight;
	newOutEdge->outToVexInd = frontInd;
	newOutEdge->next = NULL;
	return newOutEdge;
}

static EdgeNode* createEdgeNode()
{
	EdgeNode* newEdgeNode = NULL;
	newEdgeNode = (EdgeNode*)malloc(sizeof(EdgeNode));
	assert(newEdgeNode != NULL);
	newEdgeNode->inEdgeSet = NULL;
	newEdgeNode->outEdgeSet = NULL;
	return  newEdgeNode;
}

static VertexNode* createVertexNode(VertexType data)
{
	VertexNode* newVertexNode = NULL;
	newVertexNode = (VertexNode*)malloc(sizeof(VertexNode));
	assert(newVertexNode != NULL);
	newVertexNode->data = data;
	newVertexNode->vexEdgeSet = NULL;
	return newVertexNode;
}

static DVisited* createDepthVisited(int arrLen)
{
	int visitedSize;
	DVisited* newDepthVisited = NULL;

	newDepthVisited = (DVisited*)malloc(sizeof(DVisited));
	assert(newDepthVisited != NULL);

	visitedSize = arrLen * sizeof(bool);
	newDepthVisited->depthVisited = (bool*)malloc(visitedSize);
	assert(newDepthVisited->depthVisited != NULL);
	
	memset(newDepthVisited->depthVisited, false, visitedSize);
	newDepthVisited->length = 0;

	return newDepthVisited;
}

static BVisited* createBreadthVisited(int arrLen)
{
	int visitedSize;
	BVisited* newBreadthVisited = NULL;

	newBreadthVisited = (BVisited*)malloc(sizeof(BVisited));
	assert(newBreadthVisited != NULL);

	visitedSize = arrLen * sizeof(bool);
	newBreadthVisited->breadthVisited = (bool*)malloc(visitedSize);
	assert(newBreadthVisited->breadthVisited != NULL);

	memset(newBreadthVisited->breadthVisited, false, visitedSize);
	newBreadthVisited->length = 0;

	return newBreadthVisited;
}


static Stack* createStack(int stackLen)
{
	int stackSize;
	Stack* newStack = NULL;

	newStack = (Stack*)malloc(sizeof(Stack));
	assert(newStack != NULL);

	stackSize = stackLen * sizeof(int);
	newStack->stack = (int*)malloc(stackSize);
	assert(newStack->stack != NULL);

	memset(newStack->stack, -1, stackSize);
	newStack->length = 0;

	return newStack;
}


static void destroyInEdge(InEdge* inedge)
{
	if (inedge)
	{
		destroyInEdge(inedge->next);
		free(inedge);
		inedge = NULL;
	}
}


static void destroyOutEdge(OutEdge* outedge)
{
	if (outedge)
	{
		destroyOutEdge(outedge->next);
		free(outedge);
		outedge = NULL;
	}
}


static void destroyEdgeNode(EdgeNode* destEdgeNode)
{
	if (destEdgeNode)
	{
		destroyInEdge(destEdgeNode->inEdgeSet);
		destroyOutEdge(destEdgeNode->outEdgeSet);
		free(destEdgeNode);
		destEdgeNode = NULL;
	}
}


static void destroyVertexNode(VertexNode* destVertexNode)
{
	if (destVertexNode)
	{
		destroyEdgeNode(destVertexNode->vexEdgeSet);
		free(destVertexNode);
		destVertexNode = NULL;
	}
}


static void destroyDepthVisited(DVisited* depthVisited)
{
	if (depthVisited)
	{
		free(depthVisited->depthVisited);
		free(depthVisited);
		depthVisited = NULL;
	}
}


static void destroyBreadthVisited(BVisited* breadthVisited)
{
	if (breadthVisited)
	{
		free(breadthVisited->breadthVisited);
		free(breadthVisited);
		breadthVisited = NULL;
	}
}


static void destroyStack(Stack* stack)
{
	if (stack)
	{
		free(stack->stack);
		free(stack);
		stack = NULL;
	}
}


void destroyCrossGraph(CLGraph* clgp)
{
	if (clgp)
	{
		for (int i = 0; i < clgp->vexNum; i++) destroyVertexNode(clgp->crossList[i]);
	
		clgp->vexNum = 0;
		clgp->arcNum = 0;
		clgp->breadthFirstSearch = NULL;
		clgp->depthFirstSearch = NULL;
		clgp->printVexEdgeSet = NULL;
	}
}


static int stackpush(Stack* stack, int vexInd)
{
	stack->stack[stack->length++] = vexInd;
	return vexInd;
}


static int stackpop(Stack* stack)
{
	int popInd;
	popInd = stack->stack[stack->length - 1];
	stack->stack[stack->length--] = -1;
	return popInd;
}


static void initCrossLinkGraph(CLGraph* clgp, int vexNum)
{
	assert(vexNum > 0 && vexNum <= VexMaxNum);
	memset(clgp->crossList, 0, sizeof(clgp->crossList));
	clgp->vexNum = vexNum;
	clgp->arcNum = 0;
}


static void initCrossGraphCrossList(CLGraph* clgp, int *vexArr)
{
	VertexNode* vexNodeTemp;
	VertexType vexNodeData;
	for (int corsInd = 0; corsInd < clgp->vexNum; corsInd++)
	{
		vexNodeData = vexArr[corsInd];
		vexNodeTemp = createVertexNode(vexNodeData);
		/*���½��Ķ��������corsslist��*/
		clgp->crossList[corsInd] = vexNodeTemp;
	}
}


static void initCrossGraphVexRela(CLGraph* clgp, int(*vexRelaArr)[VexRelaArrNum])
{
	VertexNode* cLvexTemp;
	VertexNode* cLvexADJ;
	EdgeNode* cLvexEdge;
	EdgeType weightIn;
	EdgeType weightOut;
	InEdge* inEdge;
	OutEdge* outEdge;
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)
	*/

	for (int rearInd = 0; rearInd < clgp->vexNum; rearInd++)			// [0,1,2,3]
	{
		cLvexTemp = clgp->crossList[rearInd];
		for (int frontInd = 0; frontInd < clgp->vexNum; frontInd++)		// [0,1,2,3]
		{
			if (rearInd == frontInd) continue;
			weightIn = vexRelaArr[rearInd][frontInd];		// InEdge Weight(����)
			weightOut = vexRelaArr[frontInd][rearInd];		// OutEdge Weight(�ڽӣ�

			cLvexADJ = clgp->crossList[rearInd];
			

			if ((weightIn < VexMaxDistance && weightIn >= VexMinDistance) && (weightOut < VexMaxDistance && weightOut >= VexMinDistance))
			{
				// ���������ڽӶ���֮�䶼�����໥��ͨ�ı�ʱ
				// cLvexTemp <-> cLvexADJ

				inEdge = createInEdge(weightIn, frontInd); 
				outEdge = createOutEdge(weightOut, frontInd); 

				if (cLvexTemp->vexEdgeSet)
				{
					inEdge->next = cLvexTemp->vexEdgeSet->inEdgeSet;		// ����
					outEdge->next = cLvexTemp->vexEdgeSet->outEdgeSet;		// ����
					cLvexTemp->vexEdgeSet->inEdgeSet = inEdge;
					cLvexTemp->vexEdgeSet->outEdgeSet = outEdge;

				}
				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->inEdgeSet = inEdge;
					cLvexEdge->outEdgeSet = outEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
				clgp->arcNum++;
			}

			else if (weightIn < VexMaxDistance && weightIn >= VexMinDistance)
			{
				// cLvexTemp <- cLvexADJ
				inEdge = createInEdge(weightIn, frontInd); 
				if (cLvexTemp->vexEdgeSet) {
					inEdge->next = cLvexTemp->vexEdgeSet->inEdgeSet;		// ����
					cLvexTemp->vexEdgeSet->inEdgeSet = inEdge;
				}

				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->inEdgeSet = inEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
			}

			else if (weightOut < VexMaxDistance && weightOut >= VexMinDistance)
			{
				// cLvexTemp -> cLvexADJ
				outEdge = createOutEdge(weightOut, frontInd);
				if (cLvexTemp->vexEdgeSet) {
					outEdge->next = cLvexTemp->vexEdgeSet->outEdgeSet;		// ����
					cLvexTemp->vexEdgeSet->outEdgeSet = outEdge;
				}

				if (!cLvexTemp->vexEdgeSet)
				{
					cLvexEdge = createEdgeNode();
					cLvexEdge->outEdgeSet = outEdge;
					cLvexTemp->vexEdgeSet = cLvexEdge;
				}

				clgp->arcNum++;
			}
		}
	}

	clgp->arcNum = clgp->arcNum / 2;
}


void CrossLinkGraphInit(CLGraph* clgp, int vexNum, VertexType vexArr[], VertexType (*vexRelaArr)[VexRelaArrNum])
{
	/*
		CLGraph* clgp����ʼ����ͼ
		int vexNum����ʼ��������
		int (*vexArr)����ʼ�������б�
		int (*vexRelaArr)[VexRelaArrNum]����ʼ�������ϵ
	*/
	VertexType* vexArrTemp = vexArr;
	VertexType (*vexRelaArrTemp)[VexRelaArrNum] = vexRelaArr;

	/*��ʼ��������*/
	initCrossLinkGraph(clgp, vexNum);
	/*��ʼ�������б������㴴���������crossList��*/
	initCrossGraphCrossList(clgp, vexArrTemp);
	/*��ʼ������֮��Ĺ�ϵ��*/
	initCrossGraphVexRela(clgp, vexRelaArrTemp);
	printf("clgp->vexNum:%d, clgp->arcNum:%d\n", clgp->vexNum, clgp->arcNum);


	clgp->depthFirstSearch		= depthFirstSearch;
	clgp->breadthFirstSearch	= breadthFirstSearch;
	clgp->vertexInedgeNumber	= vertexInedgeNumber;
	clgp->vertexOutedgeNumber	= vertexOutedgeNumber;
	clgp->printVexEdgeSet		= printVexEdgeSet;
	clgp->MinimumSpanTree		=  MinimumSpanTree;


}


static int vertexInedgeNumber(CLGraph* clgp, int vexInd)
{
	EdgeNode* tempEdge;
	InEdge* tempIn;
	int inNumber = 0;

	assert(vexInd < clgp->vexNum&& vexInd >= 0);
	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	if (tempEdge == NULL) return inNumber;

	tempIn = tempEdge->inEdgeSet;
	while (tempIn)
	{
		tempIn = tempIn->next;
		inNumber++;
	}

	return inNumber;
}


static int vertexOutedgeNumber(CLGraph* clgp, int vexInd)
{
	EdgeNode* tempEdge;
	OutEdge* tempOut;
	int outNumber = 0;

	assert(vexInd < clgp->vexNum&& vexInd >= 0);
	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	if (tempEdge == NULL) return outNumber;

	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		tempOut = tempOut->next;
		outNumber++;
	}

	return outNumber;
}


static void depthvisit(CLGraph* clgp, int vexInd, DVisited* depthvisited)
{
	printf("%d ", clgp->crossList[vexInd]->data);
	depthvisited->depthVisited[vexInd] = true;
	depthvisited->length++;
}


static void breadthvisit(CLGraph* clgp, int vexInd, BVisited* breadthvisited)
{
	printf("%d ", clgp->crossList[vexInd]->data);
	breadthvisited->breadthVisited[vexInd] = true;
	breadthvisited->length++;
}


static int depthNextNeighbor(CLGraph* clgp, int vexInd, DVisited* depthvisited, Stack* stack)
{
	EdgeNode* tempEdge;
	OutEdge*  tempOut;

	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		if (!depthvisited->depthVisited[tempOut->outToVexInd])
		{
			return stackpush(stack, tempOut->outToVexInd);
		}
		else
		{
			if (stack->length == clgp->vexNum -1) return -1;
			tempOut = tempOut->next;
		}
	}
	
	if (!tempOut && stack->length) depthNextNeighbor(clgp, stackpop(stack), depthvisited, stack);
	return -1;
}


static void DFS(CLGraph* clgp, int vexInd, DVisited* depthvisited, Stack* stack)
{
	int nextVexInd;

	if (vexInd == -1) return;
	if (!depthvisited->depthVisited[vexInd])
	{
		depthvisit(clgp, vexInd, depthvisited);
		nextVexInd = depthNextNeighbor(clgp, vexInd, depthvisited, stack);
		DFS(clgp, nextVexInd, depthvisited, stack);
	}
}


/*������ȱ����㷨������ͼ������Ȩ�أ�ʮ������*/
static void depthFirstSearch(CLGraph* clgp, int vexInd)
{
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)

		1. ����һ����ʱ��ǵĶ��жԶ�����ʽ���ͳ��
		2.����һ����ջ�Ĺ����壬�Է��ʵ�˳����д洢
		3.ͨ����ȡ������ڽӶ��㣬������ȡ�������������г��ߵĶ��㶼�����ʣ����˻���һ��������ˡ�
	*/

	DVisited* depthVisited =  createDepthVisited(clgp->vexNum);
	Stack* stack = createStack(clgp->vexNum);

	DFS(clgp, vexInd, depthVisited, stack);

	destroyDepthVisited(depthVisited);
	destroyStack(stack);
	printf("\n");

}


static void breadthNextNeighbor(CLGraph* clgp, int vexInd, BVisited* breadthVisited)
{
	/*����vexInd�������һ���ٴα����㼶*/
	EdgeNode* tempEdge;
	OutEdge*  tempOut;

	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;
	tempOut = tempEdge->outEdgeSet;
	while (tempOut)
	{
		BFS(clgp, tempOut->outToVexInd, breadthVisited);
		tempOut = tempOut->next;
	}
	BFS(clgp, -1, breadthVisited);
}


static void BFS(CLGraph* clgp, int vexInd, BVisited* breadthVisited)
{
	if (vexInd == -1) return;	
	if (!breadthVisited->breadthVisited[vexInd])
	{
		breadthvisit(clgp, vexInd, breadthVisited);
		breadthNextNeighbor(clgp, vexInd, breadthVisited);		
	}
}


static void breadthFirstSearch(CLGraph* clgp, int vexInd)
{
	/*
		{65535, 1,        3, 65535},	(in Number)
		{3,     65535,    3,	 2},
		{4,     1,    65535,	 4},
		{65535, 1,    65535, 65535},

		(Out Numver)
	*/
	
	BVisited* breadthVisited = createBreadthVisited(clgp->vexNum);
	BFS(clgp, vexInd, breadthVisited);
	destroyBreadthVisited(breadthVisited);
	printf("\n");
}


void mstvisit(CLGraph* clgp, int outToVexInd, int outWeight, BVisited* mstvisited)
{
	mstvisited->length++;
	mstvisited->breadthVisited[outToVexInd] = true;
	printf("(%d %d)", outToVexInd, outWeight);

}

void getNeibhorMinWeight(CLGraph* clgp, int vexInd, BVisited* mstvisited, int* ind, int* weight)
{
	EdgeNode* tempEdge;
	InEdge* tempIn;
	OutEdge* tempOut;
	int			MinWeight = VexMaxDistance;

	tempEdge = clgp->crossList[vexInd]->vexEdgeSet;		// ������
	tempIn = tempEdge->inEdgeSet;
	tempOut = tempEdge->outEdgeSet;

	while (tempIn)
	{
		if (!mstvisited->breadthVisited[tempIn->inVexInd] && tempIn->inWeight < MinWeight)
		{
			MinWeight = *weight = tempIn->inWeight;
			*ind = tempIn->inVexInd;
		}
		else tempIn = tempIn->next;
	}

	while (tempOut)
	{
		if (!mstvisited->breadthVisited[tempOut->outToVexInd] && tempOut->outWeight < MinWeight)
		{
			MinWeight = *weight = tempOut->outWeight;
			*ind = tempOut->outToVexInd;
		}
		else tempOut = tempOut->next;
	}
}


static void MST(CLGraph* clgp, int vexInd, BVisited* mstvisited)
{
	int ind = -1, weight = 65535;
	getNeibhorMinWeight(clgp, vexInd, mstvisited, &ind, &weight);

	if (ind != -1 && !mstvisited->breadthVisited[ind])
	{
		mstvisit(clgp, ind, weight, mstvisited);
		if (clgp->vexNum > mstvisited->length) MST(clgp, ind, mstvisited);
	}
}

static void MinimumSpanTree(CLGraph* clgp, int vexInd)
{
	/*�����Ƕ���֮��Ļ�ͨ�ԣ�ֻ����һ��������Է���һ�����㣬ȫ�岻�ɻ�����*/
	BVisited* mstvisited = createBreadthVisited(clgp->vexNum);
	mstvisit(clgp, vexInd, 0, mstvisited);

	MST(clgp, vexInd, mstvisited);

}


/* Prim �㷨ʵ����С������ */
void prim(CLGraph* graph, int start) {
	int i, j, k, min;
	EdgeNode* edge;
	OutEdge* tempOut;
	bool visited[VexMaxNum]; /* �������ҵ�����С�������Ķ��� */
	int dist[VexMaxNum]; /* �����������㵽��С�������ľ��� */
	int parent[VexMaxNum]; /* ���浱ǰ��������С�������еĸ��ڵ� */

	/* ��ʼ�� visited ���顢dist ���顢parent ���� */
	for (i = 0; i < graph->vexNum; i++) {
		visited[i] = false;
		dist[i] = VexMaxDistance;
		parent[i] = -1;
	}

	/* ��ָ������㿪ʼ���� */
	visited[start] = true;
	dist[start] = 0;
	edge = graph->crossList[start]->vexEdgeSet;
	tempOut = edge->outEdgeSet;
	while (tempOut != NULL) {
		dist[tempOut->outToVexInd] = tempOut->outWeight;
		parent[tempOut->outToVexInd] = start;
		tempOut = tempOut->next;
	}

	/* ���ν�����������뵽��С�������� */
	for (i = 1; i < graph->vexNum; i++) {
		/* ѡ����һ������ */
		min = VexMaxDistance;
		for (j = 0; j < graph->vexNum; j++) {
			if (!visited[j] && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}

		/* ��ѡ�еĶ�����뵽��С�������� */
		visited[k] = true;
		edge = graph->crossList[start]->vexEdgeSet;
		tempOut = edge->outEdgeSet;
		while (tempOut != NULL) {
			if (!visited[tempOut->outToVexInd] && tempOut->outWeight < dist[tempOut->outToVexInd]) {
				dist[tempOut->outToVexInd] = tempOut->outWeight;
				parent[tempOut->outToVexInd] = k;
			}
			tempOut = tempOut->next;
		}
	}

	/* ��ӡ��С������ */
	for (i = 0; i < graph->vexNum; i++) {
		if (parent[i] != -1) {
			printf("(%d,%d) ", parent[i], i);
		}
	}
	printf("\n");
}




static void printVexEdgeSet(CLGraph* clgp)
{
	VertexNode* tempVex;
	InEdge* inEdgeset;
	OutEdge* outEdgeset;
	for (int corsind = 0; corsind < clgp->vexNum; corsind++)
	{
		tempVex = clgp->crossList[corsind];
		inEdgeset = tempVex->vexEdgeSet->inEdgeSet;
		outEdgeset = tempVex->vexEdgeSet->outEdgeSet;
		printf("\n\n***************************************\n");
		while (inEdgeset)
		{
			printf("inVexInd:%d inWeight:%d\t", inEdgeset->inVexInd, inEdgeset->inWeight);
			inEdgeset = inEdgeset->next;
		}
		printf("\n");
		printf("\n");
		while (outEdgeset)
		{
			printf("outVexInd:%d outWeight:%d\t", outEdgeset->outToVexInd, outEdgeset->outWeight);
			outEdgeset = outEdgeset->next;
		}
		printf("\n***************************************\n\n");
	}
}

